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
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"

int player_getMixerData(SSP_PLAYER* player, void* buffer, int length) {
    int bytes = BASS_ChannelGetData(player->handles->mixerChannel, buffer, length);
    if(bytes == -1) {
        bass_getError("player_getMixerData");
    }

    return bytes;
}

uint64_t player_getBytesFromSecondsForCurrentChannel(SSP_PLAYER* player, float seconds) {
    SSP_PLAYLISTITEM* item = playlist_getCurrentItem(player->playlist);
    if(item == NULL) {
        return -1;
    }

    uint64_t bytes = BASS_ChannelSeconds2Bytes(item->channel, seconds);
    if(bytes == -1) {
        bass_getError("BASS_ChannelSeconds2Bytes");
        return -1;
    }

    return bytes;
}