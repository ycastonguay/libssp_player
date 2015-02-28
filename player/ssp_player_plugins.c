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
#include "ssp_bass.h"

void player_getPathForPlugin(char* dest, const char* pathForPlugins, const char* pluginFileName) {
    if(pathForPlugins != NULL) {
        sprintf(dest, "%s/%s", pathForPlugins, pluginFileName);
    }
    else {
        strcpy(dest, pluginFileName);
    }
}

SSP_ERROR player_loadPlugins(SSP_PLAYER* player) {
    #ifdef _WIN32
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
    #elif __linux__ // also android
        char filePath[1024];

        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_ape.so");
        player->handles->apePlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->apePlugin == 0) {
            bass_getError("player_loadPlugins (APE)");
            return SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD;
        }
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_aac.so");
        player->handles->aacPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->aacPlugin == 0) {
            bass_getError("player_loadPlugins (AAC)");
            return SSP_ERROR_PLUGIN_AAC_FAILEDTOLOAD;
        }
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_alac.so");
        player->handles->alacPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->alacPlugin == 0) {
            bass_getError("player_loadPlugins (ALAC)");
            return SSP_ERROR_PLUGIN_ALAC_FAILEDTOLOAD;
        }
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbassflac.so");
        player->handles->flacPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->flacPlugin == 0) {
            bass_getError("player_loadPlugins (FLAC)");
            return SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD;
        }
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_mpc.so");
        player->handles->mpcPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->mpcPlugin == 0) {
            bass_getError("player_loadPlugins (MPC)");
            return SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD;
        }
        #if __ANDROID__
        #else
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbass_tta.so");
        player->handles->ttaPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->ttaPlugin == 0) {
            bass_getError("player_loadPlugins (TTA)");
            return SSP_ERROR_PLUGIN_TTA_FAILEDTOLOAD;
        }
        #endif
        player_getPathForPlugin(filePath, player->pathForPlugins, "libbasswv.so");
        player->handles->wvPlugin = BASS_PluginLoad(filePath, 0);
        if(player->handles->wvPlugin == 0) {
            bass_getError("player_loadPlugins (WV)");
            return SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD;
        }
    #elif TARGET_IOS
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
        if(player->handles->wvPlugin == 0) {
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
