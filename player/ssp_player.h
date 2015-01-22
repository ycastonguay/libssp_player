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

#ifndef player_ssp_player____FILEEXTENSION___
#define player_ssp_player____FILEEXTENSION___

#include <stdbool.h>
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_callbacks.h"
#include "ssp_privatestructs.h"

SSP_PLAYER* player_create();
void player_free(SSP_PLAYER* sspPlayer);

SSP_ERROR player_init(SSP_PLAYER* player, int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);

SSP_ERROR player_pause(SSP_PLAYER* player);
SSP_ERROR player_stop(SSP_PLAYER* player);
SSP_ERROR player_play(SSP_PLAYER* player);
SSP_ERROR player_previous(SSP_PLAYER* player);
SSP_ERROR player_next(SSP_PLAYER* player);
SSP_ERROR player_goTo(SSP_PLAYER* player, int index);

uint64_t player_getPosition(SSP_PLAYER* player);
SSP_ERROR player_setPosition(SSP_PLAYER* player, uint64_t position);

#endif
