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
#include <inttypes.h>
#include "../bass/bassmix.h"
#include "ssp_enums.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_convert.h"
#include "ssp_log.h"

uint64_t player_getPosition(SSP_PLAYER* player) {
    if(player->playhead->isSettingPosition || player->handles->fxChannel == 0) {
        return 0;
    }

    uint64_t position = BASS_Mixer_ChannelGetPosition(player->handles->fxChannel, BASS_POS_BYTE);
    if(position == -1) {
        bass_getError("bass_getPosition");
        return position;
    }

//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//        outputPosition = (long)((float)outputPosition * 1.5f);

    position += player->playhead->positionOffset;
    return position;
}

SSP_ERROR player_getPositionFromBytes(SSP_PLAYER* player, uint64_t bytes, SSP_POSITION* position) {
    SSP_PLAYLISTITEM* item = playlist_getCurrentItem(player->playlist);
    if(item == NULL || !item->isLoaded) {
        position->bytes = 0;
        position->samples = 0;
        position->ms = 0;
        //position->str[0] = '\0';
        convert_toStringFromMS(position->ms, position->str);
        return SSP_OK;
    }

    position->bytes = bytes;
    position->samples = convert_toSamplesFromBytes(bytes, item->bitsPerSample, item->numberOfChannels);
    position->ms = convert_toMS(position->samples, item->sampleRate);

    if(player->mixer->useFloatingPoint) {
        position->ms = position->ms / 2;
    }

    convert_toStringFromMS(position->ms, position->str);
    return SSP_OK;
}

SSP_ERROR player_getPositionFromPercentage(SSP_PLAYER* player, float percentage, SSP_POSITION* position) {
    SSP_PLAYLISTITEM* item = playlist_getCurrentItem(player->playlist);
    if(item == NULL) {
        player_getPositionFromBytes(player, 0, position);
        return SSP_ERROR_CURRENTPLAYLISTITEMISNULL;
    }

    uint64_t bytes = (uint64_t) (percentage * item->length);
    return player_getPositionFromBytes(player, bytes, position);
}

SSP_ERROR player_getPositionStruct(SSP_PLAYER* player, SSP_POSITION* position) {
    uint64_t bytes = player_getPosition(player);
    if(bytes == -1) {
        player_getPositionFromBytes(player, 0, position);
        return SSP_ERROR_FAILEDTOGETPOSITION;
    }

    return player_getPositionFromBytes(player, bytes, position);
}

SSP_ERROR player_setPosition(SSP_PLAYER* player, uint64_t position) {
    bool success;

    if(player->playhead->state == SSP_PLAYER_STATE_PAUSED) {
        player->playhead->positionAfterUnpause = position;
        return SSP_OK;
    }

    if(player->playhead->isPlayingLoop) {
        if(player->loop != NULL) {
            // If the new position is outside the current loop, stop the loop playback
			if (position < player->loop->startPositionBytes || position >= player->loop->endPositionBytes) {
                player_stopLoop(player);
            }
        }
    }

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    if(currentItem == NULL) {
        return SSP_ERROR_CURRENTPLAYLISTITEMISNULL;
    }

    SSP_ERROR error = player_removeSyncCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    success = BASS_ChannelLock(player->handles->mixerChannel, true);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return SSP_ERROR_SETPOSITION_FAILEDTOLOCKCHANNEL;
    }

    player->playhead->isSettingPosition = true;
    player->playhead->positionOffset = position;

//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//        bytes = (long)((float)bytes / 1.5f);

    success = BASS_ChannelStop(player->handles->mixerChannel);
    if(!success) {
        bass_getError("BASS_ChannelStop");
        return SSP_ERROR_SETPOSITION_FAILEDTOSTOPCHANNEL;
    }

    // Flush buffer
    success = BASS_ChannelSetPosition(currentItem->channel, 0, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition (currentItem->channel)");
        return SSP_ERROR_SETPOSITION_FAILEDTOFLUSHBUFFER;
    }
    success = BASS_ChannelSetPosition(player->handles->fxChannel, 0, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition (fxChannel)");
        return SSP_ERROR_SETPOSITION_FAILEDTOFLUSHBUFFER;
    }
    success = BASS_ChannelSetPosition(player->handles->mixerChannel, 0, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition (mixerChannel)");
        return SSP_ERROR_SETPOSITION_FAILEDTOFLUSHBUFFER;
    }

    // Set position for decode channel
    success = BASS_ChannelSetPosition(currentItem->channel, position, BASS_POS_BYTE);
    if(!success) {
        bass_getError("BASS_ChannelSetPosition (currentItem->channel)");
        return SSP_ERROR_SETPOSITION_FAILEDTOSETPOSITION;
    }

    uint64_t bytesSync = currentItem->length - position;
    error = player_setSyncCallback(player, bytesSync);
    if(error != SSP_OK) {
        return error;
    }

    if(player->playhead->state != SSP_PLAYER_STATE_PAUSED) {
        success = BASS_ChannelPlay(player->handles->mixerChannel, false);
        if(!success) {
            bass_getError("BASS_ChannelPlay");
            return SSP_ERROR_SETPOSITION_FAILEDTOPLAYCHANNEL;
        }
    }

    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("BASS_ChannelLock");
        return SSP_ERROR_SETPOSITION_FAILEDTOLOCKCHANNEL;
    }

    player->playhead->isSettingPosition = false;

    return SSP_OK;
}

SSP_ERROR player_setPositionPercentage(SSP_PLAYER* player, float position) {
    SSP_PLAYLISTITEM* item = playlist_getCurrentItem(player->playlist);
    if(item == NULL) {
        return SSP_ERROR_CURRENTPLAYLISTITEMISNULL;
    }

    uint64_t bytes = (uint64_t) ((position / 100) * item->length);
    log_textf("player_setPositionPercentage - position: %f - bytes: %"PRIu64" - length:%"PRIu64"\n", position, bytes, item->length);
    return player_setPosition(player, bytes);
}
