// Copyright © 2011-2015 Yanick Castonguay
//
// This file is part of Sessions, a music player for musicians.
//
// Sessions is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sessions is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Sessions. If not, see <http://www.gnu.org/licenses/>.

#include <string.h>
#include <stdlib.h>
#include "../bass/bass.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_loop.h"
#include "ssp_log.h"
#include "ssp_bass.h"

void CALLBACK player_loopSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user) {
    SSP_PLAYER *player = (SSP_PLAYER*)user;
    log_text("player_loopSyncProc\n");

//    if (Loop.Segments.Count - 1 > _currentSegmentIndex)
//        _currentSegmentIndex = 0;
//    else
//        _currentSegmentIndex++;

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    if(currentItem == NULL) {
        log_text("player_loopSyncProc - Aborting before currentItem is null!");
        return;
    }

    bool success = BASS_ChannelLock(player->handles->mixerChannel, true);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return;
    }

//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//    {
//        bytes = (long)((float)bytes / 1.5f);
//    }

    // Set position for the decode channel (needs to be in floating point)
	uint64_t bytes = player->loop->startPositionBytes;
    success = BASS_ChannelSetPosition(currentItem->channel, bytes * 2, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition");
        return;
    }

    // Clear buffer
    success = BASS_ChannelSetPosition(player->handles->fxChannel, 0, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition");
        return;
    }

    success = BASS_ChannelSetPosition(player->handles->mixerChannel, 0, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition");
        return;
    }

    // Set offset position (for calulating current position)
    player->playhead->positionOffset = bytes;
    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return;
    }

//    if(OnSegmentIndexChanged != null)
//        OnSegmentIndexChanged(_currentSegmentIndex);
}

SSP_ERROR player_setLoopSyncPoint(SSP_PLAYER* player, uint64_t startPosition, uint64_t endPosition, bool skipToStartPosition) {
    SSP_ERROR error = player_removeSyncCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    if(currentItem == NULL) {
        return SSP_ERROR_CURRENTPLAYLISTITEMISNULL;
    }

    bool success = BASS_ChannelLock(player->handles->mixerChannel, true);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return SSP_ERROR_FAILEDTOLOCKCHANNEL;
    }

    // Skip to the start position of the loop
    if(skipToStartPosition) {
        success = BASS_ChannelSetPosition(currentItem->channel, startPosition, BASS_POS_BYTE);
        if(!success) {
            bass_getError("BASS_ChannelSetPosition");
            return SSP_ERROR_FAILEDTOSETPOSITION;
        }

        // Clear buffer
        success = BASS_ChannelSetPosition(player->handles->fxChannel, 0, BASS_POS_BYTE);
        if(!success) {
            bass_getError("BASS_ChannelSetPosition");
            return SSP_ERROR_FAILEDTOSETPOSITION;
        }

        success = BASS_ChannelSetPosition(player->handles->mixerChannel, 0, BASS_POS_BYTE);
        if(!success) {
            bass_getError("BASS_ChannelSetPosition");
            return SSP_ERROR_FAILEDTOSETPOSITION;
        }
    }

    // Create a new sync call back for the loop end position
    uint64_t syncPosition = (endPosition - startPosition);

    player->handles->syncProcLoop = BASS_ChannelSetSync(player->handles->fxChannel, BASS_SYNC_POS | BASS_SYNC_MIXTIME, syncPosition, player_loopSyncProc, player);
    if(player->handles->syncProcLoop == 0) {
        bass_getError("BASS_ChannelSetSync");
        return SSP_ERROR_FAILEDTOSETSYNC;
    }

    // Create a new sync call back for the song end position
    uint64_t syncPositionEnd = (currentItem->length - (endPosition)); // + buffered);
    error = player_setSyncCallback(player, syncPositionEnd);
    if(error != SSP_OK) {
        return error;
    }

    // Set offset position (for calculating current position)
    if(skipToStartPosition)
        player->playhead->positionOffset = startPosition;

    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return SSP_ERROR_FAILEDTOLOCKCHANNEL;
    }

    return SSP_OK;
}

SSP_ERROR player_startLoop(SSP_PLAYER* player, SSP_LOOP* loop) {
    SSP_ERROR error = loop_validate(loop);
    if(error != SSP_OK) {
        return error;
    }

//    if (!IsPlaying)
//        Play();

//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//    {
//        positionBytes = (long)((float)positionBytes / 1.5f);
//    }

	error = player_setLoopSyncPoint(player, loop->startPositionBytes, loop->endPositionBytes, true);
    if(error != SSP_OK) {
        return error;
    }

    player->loop = malloc(sizeof(SSP_LOOP));
    loop_copy(player->loop, loop);

    player->playhead->isPlayingLoop = true;

    if(player->callbackLoopPlaybackStarted != NULL) {
        player->callbackLoopPlaybackStarted(player->callbackLoopPlaybackStartedUser);
    }

    return SSP_OK;
}

SSP_ERROR player_updateLoop(SSP_PLAYER* player, SSP_LOOP* loop) {
    SSP_ERROR error = loop_validate(loop);
    if(error != SSP_OK) {
        return error;
    }

    if(player->loop == NULL) {
        return SSP_ERROR_LOOP_INVALID;
    }

    uint64_t currentPosition = player_getPosition(player);
	uint64_t startPosition = player->loop->startPositionBytes;
	uint64_t endPosition = player->loop->endPositionBytes;
	uint64_t newStartPosition = loop->startPositionBytes;
	uint64_t newEndPosition = loop->endPositionBytes;
    bool restartLoop = false;

    // Check if the start position has changed
    if(startPosition != newStartPosition) {
        // If the current position is before the new start position...
        if(currentPosition < newStartPosition) {
            // ... then we need to start the loop again from the new start position
            log_text("player_updateLoop - currentPosition < newStartPosition -- Restarting loop!");
            restartLoop = true;
        }
    }

    // Check if the end position has changed
    if (endPosition != newEndPosition)
    {
        // If the current position exceeds the new end position...
        if (currentPosition > newEndPosition)
        {
            // ... then we need to start the loop again
            log_text("player_updateLoop - currentPosition > newEndPosition -- Restarting loop!");
            restartLoop = true;
        }
    }

    // Set the new loop
    player->loop = malloc(sizeof(SSP_LOOP));
    loop_copy(player->loop, loop);

    error = player_setLoopSyncPoint(player, newStartPosition, newEndPosition, restartLoop);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}

SSP_ERROR player_stopLoop(SSP_PLAYER* player) {
    if(player->loop == NULL) {
        return SSP_ERROR_LOOP_INVALID;
    }

    bool success = BASS_ChannelRemoveSync(player->handles->fxChannel, player->handles->syncProcLoop);
    if(!success) {
        bass_getError("BASS_ChannelRemoveSync");
        return SSP_ERROR_FAILEDTOREMOVESYNC;
    }

    player->loop = NULL;
    player->playhead->isPlayingLoop = false;

    if(player->callbackLoopPlaybackStopped != NULL) {
        player->callbackLoopPlaybackStopped(player->callbackLoopPlaybackStoppedUser);
    }

    return SSP_OK;
}
