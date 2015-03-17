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
#include "../bass/bass_fx.h"
#include "../bass/bassmix.h"
#include "ssp_player.h"
#include "ssp_log.h"

int bass_getError(char* message) {
    int error = BASS_ErrorGetCode();
    if(error == BASS_OK) {
        return BASS_OK;
    }

    log_textf("%s - BASS error: %d\n", message, error);
    return error;
}

int bass_init(int device, int sampleRate, int bufferSize, int updatePeriod) {
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        return bass_getError("bass_init (BASS_GetVersion)");
    }

    if (!BASS_Init(device, sampleRate, 0, NULL, NULL)) {
        return bass_getError("bass_init (BASS_Init)");
    }

    bool success = BASS_SetConfig(BASS_CONFIG_BUFFER, bufferSize);
    if(!success) {
        return bass_getError("bass_init (BASS_SetConfig/BASS_CONFIG_BUFFER)");
    }

    success = BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, updatePeriod);
    if(!success) {
        return bass_getError("bass_init (BASS_SetConfig/BASS_CONFIG_UPDATEPERIOD)");
    }

    success = BASS_SetConfig(BASS_CONFIG_MIXER_BUFFER, 4); // 2 == default
    if(!success) {
        return bass_getError("bass_init (BASS_SetConfig/BASS_CONFIG_MIXER_BUFFER)");
    }

    #if __ANDROID__
    success = BASS_SetConfig(BASS_CONFIG_DEV_BUFFER, 60); // 30 == default
    if(!success) {
        return bass_getError("bass_init (BASS_SetConfig/BASS_CONFIG_DEV_BUFFER)");
    }
    #endif

    return SSP_OK;
}

int bass_createMemoryStream(int frequency, int numberOfChannels, bool useFloatingPoint, STREAMPROC *streamProc, void* user) {
    DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN;
    if(useFloatingPoint) {
        flags |= BASS_SAMPLE_FLOAT;
    }
    HSTREAM stream = BASS_StreamCreate(frequency, numberOfChannels, flags, streamProc, user);
    if(stream == 0) {
        bass_getError("bass_createMemoryStream");
        return 0;
    }

    return stream;
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
        bass_getError("bass_createDecodeStream (BASS_StreamCreateFile)");
        return 0;
    }

    return stream;
}

int bass_createStreamForTimeShifting(uint32_t streamHandle, bool decode, bool useFloatingPoint) {
    DWORD flags = BASS_STREAM_PRESCAN;
    if(decode) {
        flags |= BASS_STREAM_DECODE;
    } else {
        flags |= BASS_FX_FREESOURCE;
    }
    if(useFloatingPoint) {
        flags |= BASS_SAMPLE_FLOAT;
    }
    HSTREAM stream = BASS_FX_TempoCreate(streamHandle, flags);
    if(stream == 0) {
        bass_getError("bass_createStreamForTimeShifting");
        return 0;
    }

    return stream;
}

int bass_createMixerStream(int frequency, int numberOfChannels, bool decode, bool useFloatingPoint) {
    DWORD flags = 0;
    if(decode) {
        flags |= BASS_STREAM_DECODE;
    }
    if(useFloatingPoint) {
        flags |= BASS_SAMPLE_FLOAT;
    }
    HSTREAM stream = BASS_Mixer_StreamCreate(frequency, numberOfChannels, flags);
    if(stream == 0) {
        bass_getError("bass_createMixerStream");
        return 0;
    }

    return stream;
}
