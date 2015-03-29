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
#include "../bass/bass_fx.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"

bool player_getIsShuffle(SSP_PLAYER* player) {
    return player->playhead->isShuffleEnabled;
}

SSP_ERROR player_setIsShuffle(SSP_PLAYER* player, bool shuffle) {
    player->playhead->isShuffleEnabled = shuffle;
    // TODO: Finish this
    return SSP_OK;
}

ssp_player_repeat_t player_getRepeatType(SSP_PLAYER* player) {
    return player->playhead->repeatType;
}

SSP_ERROR player_setRepeatType(SSP_PLAYER* player, ssp_player_repeat_t repeat) {
    player->playhead->repeatType = repeat;

    // Enable/disable BASS_SAMPLE_LOOP flag if repeat type is Song
    SSP_PLAYLISTITEM* item = playlist_getCurrentItem(player->playlist);
    if(item != NULL) {
        if(repeat == SSP_PLAYER_REPEAT_SONG) {
            // Enable loop mode
            BASS_ChannelFlags(item->channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
        }
        else {
            // Disable loop mode
            if (BASS_ChannelFlags(item->channel, 0, 0)&BASS_SAMPLE_LOOP) { // make sure loop is enabled
                BASS_ChannelFlags(item->channel, 0, BASS_SAMPLE_LOOP);
            }
        }
    }

    return SSP_OK;
}

float player_getVolume(SSP_PLAYER* player) {
    return player->playhead->volume;
}

SSP_ERROR player_setVolume(SSP_PLAYER* player, float volume) {
    player->playhead->volume = volume;
    // TODO: Should we keep this in SSP_PLAYHEAD when the value is found in BASS?
	bool success = BASS_ChannelSetAttribute(player->handles->mixerChannel, BASS_ATTRIB_VOL, volume);
    if(!success) {
        bass_getError("player_setVolume");
        return SSP_ERROR_FAILEDTOSETVOLUME;
    }

    return SSP_OK;
}

float player_getTimeShifting(SSP_PLAYER* player) {
    return player->playhead->timeShifting;
}

SSP_ERROR player_setTimeShifting(SSP_PLAYER* player, float timeShifting) {
    player->playhead->timeShifting = timeShifting;

    SSP_ERROR error = player_removeBPMCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    bool success = BASS_ChannelSetAttribute(player->handles->fxChannel, BASS_ATTRIB_TEMPO, timeShifting);
    if(!success) {
        bass_getError("player_setTimeShifting");
        return SSP_ERROR_FAILEDTOSETTIMESHIFTING;
    }

    error = player_addBPMCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}

int player_getPitchShifting(SSP_PLAYER* player) {
    return player->playhead->pitchShifting;
}

SSP_ERROR player_setPitchShifting(SSP_PLAYER* player, int pitchShifting) {
    player->playhead->pitchShifting = pitchShifting;

    SSP_ERROR error = player_removeBPMCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    bool success = BASS_ChannelSetAttribute(player->handles->fxChannel, BASS_ATTRIB_TEMPO_PITCH, pitchShifting);
    if(!success) {
        bass_getError("player_setPitchShifting");
        return SSP_ERROR_FAILEDTOSETPITCHSHIFTING;
    }

    error = player_addBPMCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}
