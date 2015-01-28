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
#include "ssp_playerchannels.h"

SSP_PLAYER_CHANNELS* playerChannels_create() {
    SSP_PLAYER_CHANNELS* channels = malloc(sizeof(SSP_PLAYER_CHANNELS));
    playerChannels_reset(channels);
    return channels;
}

void playerChannels_free(SSP_PLAYER_CHANNELS *channels) {
    // Nothing to free
}

void playerChannels_reset(SSP_PLAYER_CHANNELS* channels) {
    channels->streamChannel = 0;
    channels->fxChannel = 0;
    channels->mixerChannel = 0;
    channels->streamProc = NULL;
    channels->syncProc = NULL;
    channels->syncProcCount = 0;
}