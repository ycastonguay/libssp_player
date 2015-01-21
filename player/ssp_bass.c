//
//  ssp_bass.c
//  player
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

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