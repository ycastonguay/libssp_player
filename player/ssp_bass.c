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
#include <stdio.h>
#include "ssp_player.h"
#include "bass.h"
#include "bass_fx.h"

SSP_ERROR bass_getError(char* message) {
    int error = BASS_ErrorGetCode();
    if(error == BASS_OK) {
        return SSP_OK;
    }

    // TODO: Convert errors here
    printf("ssp_bass: %s - bass error code: %d\n", message, error);
    return SSP_ERROR_UNKNOWN;
}

SSP_ERROR bass_init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // Check if the correct version of BASS is loaded
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        return bass_getError("bass_init");
    }

    // Initialize default output device
    if (!BASS_Init(-1, sampleRate, 0, NULL, NULL)) {
        return bass_getError("bass_init");
    }

    // Set mixer properties
    BASS_SetConfig(BASS_CONFIG_BUFFER, bufferSize);
    BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, updatePeriod);

    // TODO: initialize plugins here

    return SSP_OK;
}

int bass_createMemoryStream(int frequency, int numberOfChannels, bool useFloatingPoint, STREAMPROC *streamProc) {
    DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN;
    if(useFloatingPoint) {
        flags |= BASS_SAMPLE_FLOAT;
    }
    HSTREAM stream = BASS_StreamCreate(frequency, numberOfChannels, flags, streamProc, NULL);
    if(stream == 0) {
        return bass_getError("bass_createMemoryStream");
    }

    return SSP_OK; // this should return the handle instead!
}

int bass_createDecodeStream(char* filePath, bool useFloatingPoint) {
    QWORD offset = 0;
    QWORD length = 0;
    DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN;
    if(useFloatingPoint) {
        flags |= BASS_SAMPLE_FLOAT;
    }
    HSTREAM stream = BASS_StreamCreateFile(FALSE, filePath, offset, length, flags);
    if(stream == 0) {
        bass_getError("bass_createDecodeStream");
        return 0;
    }

    return stream;
}

long bass_getPosition(uint32_t handle) {
    QWORD position = BASS_ChannelGetPosition(handle, BASS_POS_BYTE);
    if(position == -1) {
        bass_getError("bass_getPosition"); // TODO: How do we return an error? -1 doesn't indicate anything...
    }
    return position;
}

long bass_getLength(uint32_t handle) {
    QWORD length = BASS_ChannelGetLength(handle, BASS_POS_BYTE);
    if(length == -1) {
        bass_getError("bass_getLength"); // TODO: How do we return an error? -1 doesn't indicate anything...
    }
    return length;
}
