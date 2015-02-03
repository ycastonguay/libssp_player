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

#include <stdlib.h>
#include "ssp_enums.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "../bass/bassmix.h"

uint64_t player_getPosition(SSP_PLAYER* player) {
    if(player->playhead->isSettingPosition || player->channels->fxChannel == 0) {
        return 0;
    }

    //uint64_t position = BASS_ChannelGetPosition(player->channels->fxChannel, BASS_POS_BYTE);
    uint64_t position = BASS_Mixer_ChannelGetPosition(player->channels->fxChannel, BASS_POS_BYTE);
    if(position == -1) {
        bass_getError("bass_getPosition");
    }

    if(player->mixer->useFloatingPoint) {
        position /= 2;
    }

//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//    {
//        // Multiply by 1.5 (I don't really know why, but this works for 48000Hz and 96000Hz. Maybe a bug in BASS with FLAC files?)
//        outputPosition = (long)((float)outputPosition * 1.5f);
//    }
//

    position += player->playhead->positionOffset;
    return position;
}

SSP_ERROR player_setPosition(SSP_PLAYER* player, uint64_t position) {
    SSP_ERROR error;
    bool success;

    if(player->playhead->state == SSP_PLAYER_STATE_PAUSED) {
        player->playhead->positionAfterUnpause = position;
        return SSP_OK;
    }

    if(player->playhead->isPlayingLoop) {
//        // If the new position is outside the current loop, stop the loop playback
//        var startPosition = Loop.GetStartSegment();
//        var endPosition = Loop.GetEndSegment();
//        if (bytes < startPosition.PositionBytes || bytes >= endPosition.PositionBytes)
//        {
//            StopLoop();
//        }
    }

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);

//    // Get as much data available before locking channel
    player_removeSyncCallbacks(player);
//    long length = Playlist.CurrentItem.Channel.GetLength();

    success = BASS_ChannelLock(player->channels->mixerChannel, true);
    if(!success) {
        return bass_getError("BASS_ChannelLock");
    }

    player->playhead->isSettingPosition = true;
    player->playhead->positionOffset = position;

//    // Divide by 1.5 (I don't really know why, but this works for 48000Hz and 96000Hz. Maybe a bug in BASS with FLAC files?)
//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//        bytes = (long)((float)bytes / 1.5f);

    success = BASS_ChannelStop(player->channels->mixerChannel);
    if(!success) {
        return bass_getError("BASS_ChannelStop");
    }

    // Flush buffer
    error = bass_setPosition(currentItem->channel, 0);
    if(error != SSP_OK) {
        return error;
    }
    error = bass_setPosition(player->channels->fxChannel, 0);
    if(error != SSP_OK) {
        return error;
    }
    error = bass_setMixerPosition(player->channels->mixerChannel, 0);
    if(error != SSP_OK) {
        return error;
    }

    // Calculate position for floating point
    uint64_t bytesPosition = position;
    if (player->mixer->useFloatingPoint)
        bytesPosition *= 2;

    // Set position for decode channel
    error = bass_setPosition(currentItem->channel, bytesPosition);
    if(error != SSP_OK) {
        return error;
    }

    player_setSyncCallback(player, currentItem->length - bytesPosition);

    if(player->playhead->state != SSP_PLAYER_STATE_PAUSED) {
        success = BASS_ChannelPlay(player->channels->mixerChannel, false);
        if(!success) {
            return bass_getError("BASS_ChannelPlay");
        }
    }

    success = BASS_ChannelLock(player->channels->mixerChannel, false);
    if(!success) {
        return bass_getError("BASS_ChannelLock");
    }

    player->playhead->isSettingPosition = false;

    return SSP_OK;
}

