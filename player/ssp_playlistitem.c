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
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "../bass/bass.h"
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_playlistitem.h"
#include "ssp_log.h"

SSP_PLAYLISTITEM* playlistitem_create() {
    SSP_PLAYLISTITEM* item = malloc(sizeof(SSP_PLAYLISTITEM));
    playlistitem_reset(item);
    return item;
}

void playlistitem_free(SSP_PLAYLISTITEM *item) {
}

void playlistitem_reset(SSP_PLAYLISTITEM *item) {
    item->isLoaded = false;
    item->channel = 0;
    item->length = 0;
    item->numberOfChannels = 0;
    item->bitsPerSample = 0;
    item->sampleRate = 0;
    item->filePath = NULL;
}

void playlistitem_copy(SSP_PLAYLISTITEM *itemSrc, SSP_PLAYLISTITEM *itemDest) {
    // TODO: Is there a better way? memcpy?
    itemDest->isLoaded = itemSrc->isLoaded;
    itemDest->channel = itemSrc->channel;
    itemDest->length = itemSrc->length;
    itemDest->numberOfChannels = itemSrc->numberOfChannels;
    itemDest->bitsPerSample = itemSrc->bitsPerSample;
    itemDest->sampleRate = itemSrc->sampleRate;

    if(itemSrc->filePath != NULL) {
        size_t len = strlen(itemSrc->filePath) + 1;
        itemDest->filePath = malloc(len);
        memcpy(itemDest->filePath, itemSrc->filePath, len);
    }
//    strncpy(itemDest->filePath, itemSrc->filePath, sizeof(itemSrc->filePath));
}

SSP_ERROR playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint) {
    log_textf("playlistitem_load -- Creating stream for decoding (filePath: %s)...\n", item->filePath);
    item->channel = bass_createDecodeStream(item->filePath, useFloatingPoint);
    if(item->channel == 0) {
        return SSP_ERROR_PLAYLISTITEM_LOAD_FAILEDTOCREATEDECODESTREAM;
    }

    BASS_CHANNELINFO info;
    BASS_ChannelGetInfo(item->channel, &info);

    item->sampleRate = info.freq;
    item->numberOfChannels = info.chans;
    item->bitsPerSample = 16; // TODO: Fill this correctly, I can't find a method in BASS for this...
    item->isLoaded = true;

    item->length = BASS_ChannelGetLength(item->channel, BASS_POS_BYTE);
    if(item->length == -1) {
        return SSP_ERROR_PLAYLISTITEM_LOAD_FAILEDTOGETLENGTH;
    }

    log_textf("playlistitem_load - Load successful; length: %"PRIu64" sampleRate: %d \n", item->length, item->sampleRate);

    return SSP_OK;
}

SSP_ERROR playlist_disposeChannels(SSP_PLAYLIST *playlist) {
    SSP_ERROR error;
    if(playlist->items != NULL) {
        for(int a = 0; a < playlist_getCount(playlist); a++) {
            SSP_PLAYLISTITEM *item = playlist_getItemAt(playlist, a);
            if(item->isLoaded) {
                error = playlistitem_disposeChannel(item);
                if (error != SSP_OK) {
                    return error;
                }
            }
        }
    }

    return SSP_OK;
}
