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
#include "ssp_playerplugins.h"
#include "ssp_privatestructs.h"

SSP_PLAYER_PLUGINS* playerPlugins_create() {
    SSP_PLAYER_PLUGINS* plugins = malloc(sizeof(SSP_PLAYER_PLUGINS));
    playerPlugins_reset(plugins);
    return plugins;
}

void playerPlugins_free(SSP_PLAYER_PLUGINS *plugins) {
    // Nothing to free
    // TODO: Shall we call bass here? i.e. Do we add the player_loadPlugins here or leave in player_playback.c?
}

void playerPlugins_reset(SSP_PLAYER_PLUGINS* plugins) {
    plugins->ape = 0;
    plugins->flac = 0;
    plugins->mpc = 0;
    plugins->tta = 0;
    plugins->wv = 0;
}