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
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_eqpreset.h"
#include "ssp_playhead.h"
#include "ssp_bass.h"
#include "ssp_structs.h"
#include "ssp_privatestructs.h"

#pragma mark Initialization

SSP_PLAYER* player_create() {
    SSP_PLAYER* player = malloc(sizeof(SSP_PLAYER));
    player->playlist = playlist_create();
    player->eqPreset = eqpreset_create();
    player->playhead = playhead_create();
    player->device = malloc(sizeof(SSP_DEVICE));
    player->mixer = malloc(sizeof(SSP_MIXER));
    player->channels = malloc(sizeof(SSP_PLAYER_CHANNELS));
    player->loop = NULL;
    player->marker = NULL;
    return player;
}

void player_free(SSP_PLAYER* player) {
    if(player->playlist) {
        playlist_free(player->playlist);
        free(player->playlist);
        player->playlist = NULL;
    }
    if(player->eqPreset) {
        eqpreset_free(player->eqPreset);
        free(player->eqPreset);
        player->eqPreset = NULL;
    }
    if(player->playhead) {
        playhead_free(player->playhead);
        free(player->playhead);
        player->playhead = NULL;
    }
    if(player->device) {
        free(player->device);
        player->device = NULL;
    }
    if(player->mixer) {
        free(player->mixer);
        player->mixer = NULL;
    }
    if(player->channels) {
        free(player->channels);
        player->channels = NULL;
    }
    if(player->loop) {
        free(player->loop);
        player->loop = NULL;
    }
    if(player->marker) {
        free(player->marker);
        player->marker = NULL;
    }
}

SSP_ERROR player_init(SSP_PLAYER* player, int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // TODO: validate input

    // Set mixer properties
    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    // Reset playhead
    playhead_reset(player->playhead);

    SSP_ERROR error = bass_init(device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return error;
}

#pragma mark Callbacks

DWORD CALLBACK player_streamProc(HSTREAM handle, float *buffer, DWORD length, void *user) {
    return 0;
}

#pragma mark Playback

SSP_ERROR player_pause(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_stop(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_play(SSP_PLAYER* player) {

    printf("player_play\n");
    if(player->playhead->isPlaying) {
        if(player->playhead->isPlayingLoop) {
            // TODO: stop loop
        }

        player_stop(player);
    }

    printf("player_play - Getting current index and count...\n");
    int currentIndex = player->playlist->currentIndex;
    int count = playlist_getCount(player->playlist);

    int channelsToLoad = count - currentIndex;
    if(channelsToLoad > 2)
        channelsToLoad = 2;

    if(channelsToLoad == 0) {
        printf("player_play - ERROR: There are no channels to load!\n");
        return SSP_ERROR_UNKNOWN;
    }

    for(int a = currentIndex; a < currentIndex + channelsToLoad; a++) {
        printf("player_play - Loading playlist item %d...\n", a);
        playlistitem_load(playlist_getItemAt(player->playlist, a), player->mixer->useFloatingPoint);
    }

    // Default output driver (i.e. DirectSound)
    printf("player_play - Setting stream channel and proc...\n");
    player->channels->streamProc = (STREAMPROC*)player_streamProc;
    player->channels->streamChannel = bass_createMemoryStream(player->mixer->sampleRate, 2, player->mixer->useFloatingPoint, player->channels->streamProc);
    // fx channel here

    return SSP_OK;
}

SSP_ERROR player_previous(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_next(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_goTo(SSP_PLAYER* player, int index) {
    return SSP_OK;
}

