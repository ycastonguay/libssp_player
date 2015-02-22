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

void player_getPathForPlugin(const char* dest, const char* pathForPlugins, const char* pluginFileName) {
    if(pathForPlugins != NULL) {
        sprintf(dest, "%s/%s", pathForPlugins, pluginFileName);
    }
    else {
        strcpy(dest, pluginFileName);
    }
}

SSP_ERROR player_loadPlugins(SSP_PLAYER* player) {
    #ifdef _WIN32 // Windows
        player->handles->apePlugin = BASS_PluginLoad("bass_ape.dll", 0);
		if (player->handles->apePlugin == 0) {
			bass_getError("player_loadPlugins (APE)");
			return SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD;
		}
		player->handles->aacPlugin = BASS_PluginLoad("bass_aac.dll", 0);
		if (player->handles->aacPlugin == 0) {
			bass_getError("player_loadPlugins (AAC)");
			return SSP_ERROR_PLUGIN_AAC_FAILEDTOLOAD;
		}
		player->handles->alacPlugin = BASS_PluginLoad("bass_alac.dll", 0);
		if (player->handles->alacPlugin == 0) {
			bass_getError("player_loadPlugins (ALAC)");
			return SSP_ERROR_PLUGIN_ALAC_FAILEDTOLOAD;
		}
		player->handles->flacPlugin = BASS_PluginLoad("bassflac.dll", 0);
		if (player->handles->flacPlugin == 0) {
			bass_getError("player_loadPlugins (FLAC)");
			return SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD;
		}
		player->handles->mpcPlugin = BASS_PluginLoad("bass_mpc.dll", 0);
		if (player->handles->mpcPlugin == 0) {
			bass_getError("player_loadPlugins (MPC)");
			return SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD;
		}
		player->handles->ttaPlugin = BASS_PluginLoad("bass_tta.dll", 0);
		if (player->handles->ttaPlugin == 0) {
			bass_getError("player_loadPlugins (TTA)");
			return SSP_ERROR_PLUGIN_TTA_FAILEDTOLOAD;
		}
		player->handles->wmaPlugin = BASS_PluginLoad("basswma.dll", 0);
		if (player->handles->wmaPlugin == 0) {
			bass_getError("player_loadPlugins (WMA)");
			return SSP_ERROR_PLUGIN_WMA_FAILEDTOLOAD;
		}
		player->handles->wvPlugin = BASS_PluginLoad("basswv.dll", 0);
		if (player->handles->wvPlugin == 0) {
			bass_getError("player_loadPlugins (WV)");
			return SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD;
		}
    #elif __linux__ // Linux
        //BASS_PluginLoad("libbassflac.so", 0);
        // TODO: Complete implementation
    #elif TARGET_IOS // iOS
        extern void BASS_APEplugin, BASSFLACplugin, BASS_MPCplugin, BASSWVplugin;
        player->handles->apePlugin = BASS_PluginLoad(&BASS_APEplugin, 0);
        if(player->handles->apePlugin == 0) {
			bass_getError("player_loadPlugins (APE)");
            return SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD;
        }
        player->handles->flacPlugin = BASS_PluginLoad(&BASSFLACplugin, 0);
        if(player->handles->flacPlugin == 0) {
			bass_getError("player_loadPlugins (FLAC)");
            return SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD;
        }
        player->handles->mpcPlugin = BASS_PluginLoad(&BASS_MPCplugin, 0);
        if(player->handles->mpcPlugin == 0) {
			bass_getError("player_loadPlugins (MPC)");
            return SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD;
        }
        player->handles->wvPlugin = BASS_PluginLoad(&BASSWVplugin, 0);
        if(player->handles->wvPlugin == 0) {
			bass_getError("player_loadPlugins (WV)");
            return SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD;
        }
    #elif TARGET_OSX
        char filePath[1024];

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_ape.dylib");
        player->handles->apePlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->apePlugin == 0) {
			bass_getError("player_loadPlugins (APE)");
            return SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD;
        }

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbassflac.dylib");
        player->handles->flacPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->flacPlugin == 0) {
			bass_getError("player_loadPlugins (FLAC)");
            return SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD;
        }

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_mpc.dylib");
        player->handles->mpcPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->mpcPlugin == 0) {
			bass_getError("player_loadPlugins (MPC)");
            return SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD;
        }

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_tta.dylib");
        player->handles->ttaPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->ttaPlugin == 0) {
			bass_getError("player_loadPlugins (TTA)");
            return SSP_ERROR_PLUGIN_TTA_FAILEDTOLOAD;
        }

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbasswv.dylib");
        player->handles->wvPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->wvPlugin == 0) 
			bass_getError("player_loadPlugins (WV)");
            return SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD;
        }
    #endif

    return SSP_OK;
}

SSP_ERROR player_freePlugins(SSP_PLAYER* player) {
    bool success = false;
    if(player->handles->apePlugin > 0) {
        success = BASS_PluginFree(player->handles->apePlugin);
        if(!success) {
            bass_getError("player_freePlugins (APE)");
            return SSP_ERROR_PLUGIN_APE_FAILEDTOFREE;
        }
		player->handles->apePlugin = 0;
    }
	if (player->handles->aacPlugin > 0) {
		success = BASS_PluginFree(player->handles->aacPlugin);
		if (!success) {
			bass_getError("player_freePlugins (AAC)");
			return SSP_ERROR_PLUGIN_AAC_FAILEDTOFREE;
		}
		player->handles->aacPlugin = 0;
	}
	if (player->handles->alacPlugin > 0) {
		success = BASS_PluginFree(player->handles->alacPlugin);
		if (!success) {
			bass_getError("player_freePlugins (ALAC)");
			return SSP_ERROR_PLUGIN_ALAC_FAILEDTOFREE;
		}
		player->handles->alacPlugin = 0;
	}
	if (player->handles->flacPlugin > 0) {
        success = BASS_PluginFree(player->handles->flacPlugin);
        if(!success) {
            bass_getError("player_freePlugins (FLAC)");
            return SSP_ERROR_PLUGIN_FLAC_FAILEDTOFREE;
        }
		player->handles->flacPlugin = 0;
    }
    if(player->handles->mpcPlugin > 0) {
        success = BASS_PluginFree(player->handles->mpcPlugin);
        if(!success) {
            bass_getError("player_freePlugins (MPC)");
            return SSP_ERROR_PLUGIN_MPC_FAILEDTOFREE;
        }
		player->handles->mpcPlugin = 0;
    }
    if(player->handles->ttaPlugin > 0) {
        success = BASS_PluginFree(player->handles->ttaPlugin);
        if(!success) {
            bass_getError("player_freePlugins (TTA)");
            return SSP_ERROR_PLUGIN_TTA_FAILEDTOFREE;
        }
		player->handles->ttaPlugin = 0;
    }
	if (player->handles->wmaPlugin > 0) {
		success = BASS_PluginFree(player->handles->wmaPlugin);
		if (!success) {
			bass_getError("player_freePlugins (WMA)");
			return SSP_ERROR_PLUGIN_WMA_FAILEDTOFREE;
		}
		player->handles->wmaPlugin = 0;
	}
	if (player->handles->wvPlugin > 0) {
        success = BASS_PluginFree(player->handles->wvPlugin);
        if(!success) {
            bass_getError("player_freePlugins (WV)");
            return SSP_ERROR_PLUGIN_WV_FAILEDTOFREE;
        }
		player->handles->wvPlugin = 0;
    }

    return SSP_OK;
}

SSP_ERROR player_getBassVersions() {
    uint32_t bassVersion = BASS_GetVersion();
    uint32_t bassFXVersion = BASS_FX_GetVersion();
    uint32_t bassMixVersion = BASS_Mixer_GetVersion();
    uint32_t bassEncVersion = BASS_Encode_GetVersion();
    if (HIWORD(bassVersion) != BASSVERSION || LOWORD(bassVersion)<0x100) {
        return SSP_ERROR_BASS_VERSION;
    }

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
    // TODO: validate input

    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    player->device = device_create();
    player->device->deviceId = deviceId;

    playhead_reset(player->playhead);

    log_textf("player_initDevice: Initializing device (%d Hz, ms buffer: %d, update period: %d, floatingPoint: %d)\n", sampleRate, bufferSize, updatePeriod, useFloatingPoint);
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
    player->mixer->bufferSize = bufferSize;

    bool success = BASS_SetConfig(BASS_CONFIG_BUFFER, bufferSize);
    if(!success) {
        bass_getError("BASS_SetConfig");
        return SSP_ERROR_PLAYHEAD_FAILEDTOSETBUFFERSIZE;
    }

    return SSP_OK;
}

SSP_ERROR player_setUpdatePeriod(SSP_PLAYER* player, int updatePeriod) {
    player->mixer->updatePeriod = updatePeriod;

    bool success = BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, updatePeriod);
    if(!success) {
        bass_getError("BASS_SetConfig");
        return SSP_ERROR_PLAYHEAD_FAILEDTOSETUPDATEPERIOD;
    }

    return SSP_OK;
}
