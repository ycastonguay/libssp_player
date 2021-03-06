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
#include "../bass/bass.h"
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_playlistitem.h"
#include "ssp_log.h"
#include "ssp_util.h"

SSP_PLAYLISTITEM* playlistitem_create() {
    SSP_PLAYLISTITEM* item = malloc(sizeof(SSP_PLAYLISTITEM));
    playlistitem_reset(item);
    return item;
}

void playlistitem_free(SSP_PLAYLISTITEM *item) {
}

void playlistitem_reset(SSP_PLAYLISTITEM *item) {
	item->id = -1;
	item->isLoaded = false;	
    item->channel = 0;
    item->length = 0;
    item->numberOfChannels = 0;
    item->bitsPerSample = 0;
    item->sampleRate = 0;
    item->filePath = NULL;
	item->audioFileId = NULL;
}

void playlistitem_copy(SSP_PLAYLISTITEM *itemSrc, SSP_PLAYLISTITEM *itemDest) {
	itemDest->id = itemSrc->id;
    itemDest->isLoaded = itemSrc->isLoaded;
    itemDest->channel = itemSrc->channel;
    itemDest->length = itemSrc->length;
    itemDest->numberOfChannels = itemSrc->numberOfChannels;
    itemDest->bitsPerSample = itemSrc->bitsPerSample;
    itemDest->sampleRate = itemSrc->sampleRate;
    itemDest->filePath = copystr((char *) itemDest->filePath, itemSrc->filePath);
	itemDest->audioFileId = copystr((char *)itemDest->audioFileId, itemSrc->audioFileId);
}

SSP_ERROR playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint) {
    log_textf("playlistitem_load -- Creating stream for decoding (filePath: %s)...\n", item->filePath);
    item->channel = bass_createDecodeStream((char *)item->filePath, useFloatingPoint);
    if(item->channel == 0) {
        return SSP_ERROR_FAILEDTOCREATEDECODESTREAM;
    }

    BASS_CHANNELINFO info;
    bool success = BASS_ChannelGetInfo(item->channel, &info);
	if (!success) {
		return SSP_ERROR_FAILEDTOGETCHANNELINFO;
	}

    item->sampleRate = info.freq >= 44100 && info.freq <= 96000 ? info.freq : 44100;
    item->numberOfChannels = info.chans >= 1 && info.chans <= 2 ? info.chans : 2;
	item->bitsPerSample = info.origres == 16 || info.origres == 24 ? info.origres : 16; // sometimes BASS cannot detect origres correctly on OSX.
    item->isLoaded = true;
    item->length = BASS_ChannelGetLength(item->channel, BASS_POS_BYTE);
    if(item->length == -1) {
        return SSP_ERROR_FAILEDTOGETLENGTH;
    }

    log_textf("playlistitem_load - Load successful; length: %"PRIu64" sampleRate: %d \n", item->length, item->sampleRate);

    return SSP_OK;
}

