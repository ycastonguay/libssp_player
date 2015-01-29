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
#include "../bass/bass_fx.h"
#include "../bass/bassmix.h"

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

SSP_ERROR bass_start() {
    bool success = BASS_Start();
    if(!success) {
        return bass_getError("bass_start");
    }
    return SSP_OK;
}

SSP_ERROR bass_stop() {
    bool success = BASS_Stop();
    if(!success) {
        return bass_getError("bass_stop");
    }
    return SSP_OK;
}

SSP_ERROR bass_pause() {
    bool success = BASS_Pause();
    if(!success) {
        return bass_getError("bass_pause");
    }
    return SSP_OK;
}

SSP_ERROR bass_play(uint32_t handle, bool restart) {
    bool success = BASS_ChannelPlay(handle, restart);
    if(!success) {
        return bass_getError("bass_play");
    }
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
        bass_getError("bass_createDecodeStream");
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

SSP_ERROR bass_addChannelToMixer(uint32_t mixerHandle, uint32_t channelHandle) {
    bool success = BASS_Mixer_StreamAddChannel(mixerHandle, channelHandle, BASS_MIXER_BUFFER);
    if(!success) {
        return bass_getError("bass_addChannel");
    }
    return SSP_OK;
}

int bass_setMixerSyncProc(uint32_t handle, uint64_t position, void* syncProc) {
    HSYNC sync = BASS_Mixer_ChannelSetSync(handle, BASS_SYNC_POS, position, syncProc, 0);
    if(sync == 0) {
        return bass_getError("bass_setMixerSyncProc");
    }
    return sync;
}

uint64_t bass_getPosition(uint32_t handle) {
    QWORD position = BASS_ChannelGetPosition(handle, BASS_POS_BYTE);
    if(position == -1) {
        bass_getError("bass_getPosition"); // TODO: How do we return an error? -1 doesn't indicate anything...
    }
    return position;
}

uint64_t bass_getLength(uint32_t handle) {
    QWORD length = BASS_ChannelGetLength(handle, BASS_POS_BYTE);
    if(length == -1) {
        bass_getError("bass_getLength"); // TODO: How do we return an error? -1 doesn't indicate anything...
    }
    return length;
}

SSP_ERROR bass_setPosition(uint32_t handle, uint64_t position) {
    bool success = BASS_ChannelSetPosition(handle, position, BASS_POS_BYTE);
    if(!success) {
        return bass_getError("bass_setPosition");
    }
    return SSP_OK;
}

SSP_ERROR bass_setMixerPosition(uint32_t handle, uint64_t position) {
    bool success = BASS_Mixer_ChannelSetPosition(handle, position, BASS_POS_BYTE);
    if(!success) {
        return bass_getError("bass_setMixerPosition");
    }
    return SSP_OK;
}
