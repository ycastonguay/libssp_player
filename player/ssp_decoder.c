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

#include "ssp_decoder.h"
#include "ssp_errors.h"
#include "ssp_bass.h"

uint32_t decoder_createStream(char* filePath, bool useFloatingPoint) {
    uint32_t handle = bass_createDecodeStream(filePath, useFloatingPoint);
    if(handle == 0) {
        //return SSP_ERROR_FAILEDTOCREATEDECODESTREAM;
        return 0; // SSP error codes might be mixed up with actual handle values
    }

    return handle;
}

SSP_ERROR decoder_freeStream(uint32_t handle) {
    bool success = BASS_StreamFree(handle);
    if(!success) {
        bass_getError("decoder_freeStream");
        return SSP_ERROR_FAILEDTOFREESTREAM;
    }
    return SSP_OK;
}

uint64_t decoder_getLength(uint32_t handle) {
    uint64_t length = BASS_ChannelGetLength(handle, BASS_POS_BYTE);
    if(length == -1) {
        bass_getError("decoder_getLength");
        return 0;
    }
    return length;
}

uint64_t decoder_getData(uint32_t handle, void* buffer, int length) {
    int bytes = BASS_ChannelGetData(handle, buffer, length);
    if(bytes == -1) {
        bass_getError("decoder_getData");
    }

    return bytes;
}