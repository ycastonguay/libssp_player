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
#include "bass.h"

SSP_ERROR bass_init(DWORD device, DWORD sampleRate, DWORD bufferSize, DWORD updatePeriod, bool useFloatingPoint) {
    // Check if the correct version of BASS is loaded
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        return SSP_ERROR_UNKNOWN;
    }

    // Initialize default output device
    if (!BASS_Init(-1, sampleRate, 0, NULL, NULL)) {
        return SSP_ERROR_UNKNOWN;
    }

    // Set mixer properties
    BASS_SetConfig(BASS_CONFIG_BUFFER, bufferSize);
    BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, updatePeriod);

    // TODO: initialize plugins here

    return SSP_ERROR_OK;
}