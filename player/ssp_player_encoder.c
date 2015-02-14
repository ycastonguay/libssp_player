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

#include <stdio.h>
#include "../bass/bassenc.h"
#include "ssp_player.h"
#include "ssp_bass.h"

#define COCOA_AUDIOUNIT_ADTS   1633973363 // 'adts'
#define COCOA_AUDIOUNIT_MP4F   1836069990 // 'mp4f'
#define COCOA_AUDIOUNIT_M4AF   1832149350 // 'm4af'
#define COCOA_AUDIOUNIT_AAC    1633772320 // 'aac '
#define COCOA_AUDIOUNIT_ALAC   1634492771 // 'alac'

SSP_ERROR player_startEncode(SSP_PLAYER* player, ssp_player_encoder_t encoder) {
    //sprintf(com,"lame -r -s 44100 -b %d -",bitrate); // add "-x" for LAME versions pre-3.98
    //sprintf(com,"oggenc -r -R 44100 -M %d -m %d -",bitrate,bitrate);

    DWORD ftype = COCOA_AUDIOUNIT_ADTS;
    DWORD atype = COCOA_AUDIOUNIT_AAC;
    int bitrate = 128;
    DWORD flags = BASS_ENCODE_NOHEAD | BASS_ENCODE_AUTOFREE;
    switch(encoder) {
        case SSP_PLAYER_ENCODER_OGG:
            player->handles->encoder = BASS_Encode_Start(player->handles->mixerChannel, "oggenc -r -R 44100 -M 128 -m 128 -", flags, NULL, NULL);
            break;
        case SSP_PLAYER_ENCODER_AAC:
            #if TARGET_IOS || TARGET_OSX
            player->handles->encoder = BASS_Encode_StartCA(player->handles->mixerChannel, ftype, atype, BASS_ENCODE_AUTOFREE, bitrate, NULL, NULL);
            if(player->handles->encoder == 0) {
                bass_getError("BASS_Encode_StartCA");
                return SSP_ERROR_ENCODER_FAILEDTOSTART;
            }
            #endif
            break;
        case SSP_PLAYER_ENCODER_MP3:
            player->handles->encoder = BASS_Encode_Start(player->handles->mixerChannel, "lame -r -x -s 44100 -b 128 -", flags, NULL, NULL);
            break;
    }

    return SSP_OK;
}

SSP_ERROR player_stopEncode(SSP_PLAYER* player) {
    bool success = BASS_Encode_Stop(player->handles->encoder);
    if(!success) {
        bass_getError("BASS_Encode_Stop");
        return SSP_ERROR_ENCODER_FAILEDTOSTOP;
    }
    player->handles->encoder = 0;
    return SSP_OK;
}

SSP_ERROR player_startCast(SSP_PLAYER* player, SSP_CAST_SERVER* server) {
    if(player->handles->encoder == 0) {
        return SSP_ERROR_CAST_ENCODERNOTFOUND;
    }

    bool success = BASS_Encode_CastInit(player->handles->encoder, server->url, server->password, BASS_ENCODE_TYPE_MP3, "name", "url", "genre", NULL, NULL, server->bitrate, TRUE);
    if(!success) {
        bass_getError("BASS_Encode_CastInit");
        return SSP_ERROR_CAST_FAILEDTOINIT;
    }

    return SSP_OK;
}

SSP_ERROR player_stopCast(SSP_PLAYER* player) {
    // TODO: Not sure how, simply stop encoder?
    return SSP_OK;
}
