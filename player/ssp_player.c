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
#include "../bass/bass.h"
#include "../bass/bass_fx.h"
#include "../bass/bassmix.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_eqpreset.h"
#include "ssp_playhead.h"
#include "ssp_bass.h"
#include "ssp_playerhandles.h"
#include "ssp_mixer.h"
#include "ssp_device.h"
#include "ssp_log.h"

#pragma mark Initialization

SSP_PLAYER* player_create() {
    SSP_PLAYER* player = malloc(sizeof(SSP_PLAYER));
    player->playlist = playlist_create();
    player->eqPreset = eqpreset_create();
    player->playhead = playhead_create();
    player->mixer = mixer_create();
    player->handles = playerHandles_create();
    player->device = NULL;
    player->pathForPlugins = NULL;
    player->loop = NULL;
    player->callbackStateChanged = NULL;
    player->callbackStateChangedUser = NULL;
    player->callbackLoopPlaybackStarted = NULL;
    player->callbackLoopPlaybackStartedUser = NULL;
    player->callbackLoopPlaybackStopped = NULL;
    player->callbackLoopPlaybackStoppedUser = NULL;
    player->callbackAudioInterrupted = NULL;
    player->callbackAudioInterruptedUser = NULL;
    player->callbackBPMDetected = NULL;
    player->callbackBPMDetectedUser = NULL;

    return player;
}

SSP_ERROR player_free(SSP_PLAYER* player) {
    player_freePlugins(player);

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
        device_free(player->device);
        free(player->device);
        player->device = NULL;
    }
    if(player->mixer) {
        mixer_free(player->mixer);
        free(player->mixer);
        player->mixer = NULL;
    }
    if(player->handles) {
        playerHandles_free(player->handles);
        free(player->handles);
        player->handles = NULL;
    }
    if(player->loop) {
        free(player->loop);
        player->loop = NULL;
    }

    return SSP_OK;
}

SSP_ERROR player_getBassVersions() {
    uint32_t bassVersion = BASS_GetVersion();
    if (HIWORD(bassVersion) != BASSVERSION || LOWORD(bassVersion)<0x100) {
        return SSP_ERROR_BASS_VERSION;
    }

    uint32_t bassFXVersion = BASS_FX_GetVersion();
    uint32_t bassMixVersion = BASS_Mixer_GetVersion();
    uint32_t bassEncVersion = BASS_Encode_GetVersion();
    log_textf("libbass version %d || libbass_fx version %d || libbassmix version %d || libbassenc version %d\n", bassVersion, bassFXVersion, bassMixVersion, bassEncVersion);

    return SSP_OK;
}

SSP_ERROR player_init(SSP_PLAYER* player) {
    SSP_ERROR error = player_getBassVersions();
    if(error != SSP_OK) {
        return error;
    }

    error = player_loadPlugins(player);
    if(error != SSP_OK) {
        return error;
    }

    playhead_reset(player->playhead);

    return SSP_OK;
}

SSP_ERROR player_initDevice(SSP_PLAYER* player, int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    if(sampleRate < 44100 || sampleRate > 96000) {
        return SSP_ERROR_SAMPLERATE_INVALID;
    }
    if(bufferSize < 10 || bufferSize > 5000) {
        return SSP_ERROR_BUFFERSIZE_INVALID;
    }
    if(updatePeriod < 5 || updatePeriod > 100) {
        return SSP_ERROR_UPDATEPERIOD_INVALID;
    }

    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    player->device = device_create();
    player->device->deviceId = deviceId;

    playhead_reset(player->playhead);

    log_textf("player_initDevice: Initializing device (id: %d sampleRate: %d - bufferSize: %d - updatePeriod: %d - useFloatingPoint: %d)\n", deviceId, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    SSP_ERROR error = bass_init(deviceId, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    if(error != SSP_OK) {
        return error;
    }

    player->device->isInitialized = true;
    player_updateState(player, SSP_PLAYER_STATE_INITIALIZED);

    return SSP_OK;
}

SSP_ERROR player_freeDevice(SSP_PLAYER* player) {
    // Channels should be freed already with player_stop()
    bool success = BASS_Free();
    if(!success) {
        return SSP_ERROR_DEVICE_FAILEDTOFREE;
    }

    device_free(player->device);
    player->device = NULL;

    return SSP_OK;
}

void player_updateState(SSP_PLAYER* player, ssp_player_state_t state) {
    player->playhead->state = state;

    if(player->callbackStateChanged != NULL) {
        player->callbackStateChanged(player->callbackStateChangedUser, state);
    }
}

SSP_ERROR player_setBufferSize(SSP_PLAYER* player, int bufferSize) {
    if(bufferSize < 10 || bufferSize > 5000) {
        return SSP_ERROR_BUFFERSIZE_INVALID;
    }

    player->mixer->bufferSize = bufferSize;

    bool success = BASS_SetConfig(BASS_CONFIG_BUFFER, bufferSize);
    if(!success) {
        bass_getError("BASS_SetConfig");
        return SSP_ERROR_PLAYHEAD_FAILEDTOSETBUFFERSIZE;
    }

    return SSP_OK;
}

SSP_ERROR player_setUpdatePeriod(SSP_PLAYER* player, int updatePeriod) {
    if(updatePeriod < 5 || updatePeriod > 100) {
        return SSP_ERROR_UPDATEPERIOD_INVALID;
    }

    player->mixer->updatePeriod = updatePeriod;

    bool success = BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, updatePeriod);
    if(!success) {
        bass_getError("BASS_SetConfig");
        return SSP_ERROR_PLAYHEAD_FAILEDTOSETUPDATEPERIOD;
    }

    return SSP_OK;
}
