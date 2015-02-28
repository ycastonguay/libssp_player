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
#include "../vector/vector.h"
#include "ssp_playerhandles.h"

SSP_PLAYER_HANDLES *playerHandles_create() {
    SSP_PLAYER_HANDLES *handles = malloc(sizeof(SSP_PLAYER_HANDLES));
    playerHandles_reset(handles);

    handles->syncProcHandles = malloc(sizeof(vector));
    vector_init(handles->syncProcHandles);

    return handles;
}

void playerHandles_free(SSP_PLAYER_HANDLES *handles) {
    if(handles->syncProcHandles) {
        vector_free(handles->syncProcHandles);
        free(handles->syncProcHandles);
        handles->syncProcHandles = NULL;
    }
}

void playerHandles_reset(SSP_PLAYER_HANDLES *handles) {
    handles->streamChannel = 0;
    handles->fxChannel = 0;
    handles->mixerChannel = 0;

    handles->apePlugin = 0;
    handles->flacPlugin = 0;
    handles->mpcPlugin = 0;
    handles->ttaPlugin = 0;
    handles->wvPlugin = 0;

    handles->eqFX = 0;

    handles->syncProcLoop = 0;

    handles->encoder = 0;

    handles->streamProc = NULL;
    handles->syncProc = NULL;

    handles->syncProcHandles = NULL;
}