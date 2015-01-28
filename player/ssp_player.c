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
#include "ssp_playerchannels.h"
#include "ssp_structs.h"
#include "ssp_privatestructs.h"
#include "bassmix.h"
#include "ssp_mixer.h"
#include "ssp_device.h"

#pragma mark Initialization

SSP_PLAYER* player_create() {
    SSP_PLAYER* player = malloc(sizeof(SSP_PLAYER));
    player->playlist = playlist_create();
    player->eqPreset = eqpreset_create();
    player->playhead = playhead_create();
    //player->device = device_create(); // uses default device
    player->mixer = mixer_create();
    player->channels = playerChannels_create();
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
        device_free(player->device);
        free(player->device);
        player->device = NULL;
    }
    if(player->mixer) {
        mixer_free(player->mixer);
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

SSP_ERROR player_loadPlugins(SSP_PLAYER* player) {

//#ifdef _WIN32 // Windows/CE
//    BASS_PluginLoad("bassflac.dll", 0);
//#elif __linux__ // Linux
//    BASS_PluginLoad("libbassflac.so", 0);
//#elif TARGET_OS_IPHONE // iOS
//    extern void BASSFLACplugin;
//    BASS_PluginLoad(&BASSFLACplugin, 0);
//#else // OSX
//    BASS_PluginLoad("libbassflac.dylib", 0);
//#endif

    return SSP_OK;
}

SSP_ERROR player_init(SSP_PLAYER* player) {
    SSP_ERROR error;

    error = player_loadPlugins(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}

SSP_ERROR player_initDevice(SSP_PLAYER* player, int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // TODO: validate input

    // Set mixer properties
    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    // Set device properties
    player->device = device_create();
    player->device->deviceId = deviceId;

    // Reset playhead
    playhead_reset(player->playhead);

    SSP_ERROR error = bass_init(deviceId, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return error;
}

SSP_ERROR player_freeDevice(SSP_PLAYER* player) {

    // Channels should be freed already with player_stop()

    // Free BASS resources
    bool success = BASS_Free();
    if(!success) {
        return SSP_ERROR_UNKNOWN;
    }

    // Free device
    device_free(player->device);
    player->device = NULL;

    return SSP_OK;
}


