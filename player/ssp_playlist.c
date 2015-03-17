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
#include <string.h>
#include "../vector/vector.h"
#include "../bass/bass.h"
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_playlistitem.h"
#include "ssp_log.h"
#include "ssp_util.h"

SSP_PLAYLIST* playlist_create() {
    SSP_PLAYLIST* playlist = malloc(sizeof(SSP_PLAYLIST));
    playlist->items = malloc(sizeof(vector));
    vector_init(playlist->items);

	playlist->nextId = -1;
    playlist->currentIndex = 0;
    playlist->currentMixerIndex = 0;
    playlist->name = NULL;
    playlist->callbackPlaylistIndexChanged = NULL;
    playlist->callbackPlaylistIndexChangedUser = NULL;
    playlist->callbackPlaylistEnded = NULL;
    playlist->callbackPlaylistEndedUser = NULL;

    return playlist;
}

void playlist_free(SSP_PLAYLIST *playlist) {
    if(playlist->items) {
        vector_free(playlist->items);
        free(playlist->items);
        playlist->items = NULL;
    }
//    if(playlist->name) {
//        free(playlist->name);
//        playlist->name = NULL;
//    }
    playlist->callbackPlaylistIndexChanged = NULL;
    playlist->callbackPlaylistIndexChangedUser = NULL;
    playlist->callbackPlaylistEnded = NULL;
    playlist->callbackPlaylistEndedUser = NULL;
}

SSP_ERROR playlistitem_disposeChannel(SSP_PLAYLISTITEM *item) {
    bool success = BASS_ChannelStop(item->channel);
    if(!success) {
        bass_getError("BASS_ChannelStop");
        return SSP_ERROR_PLAYLISTITEM_DISPOSE_FAILEDTOSTOPCHANNEL;
    }

    success = BASS_StreamFree(item->channel);
    if(!success) {
        bass_getError("BASS_StreamFree");
        return SSP_ERROR_PLAYLISTITEM_DISPOSE_FAILEDTOFREESTREAM;
    }

    item->isLoaded = false;
    item->channel = 0;
    item->length = 0;
    item->numberOfChannels = 0;
    item->sampleRate = 0;

    return SSP_OK;
}

SSP_ERROR playlist_addItem(SSP_PLAYLIST *playlist, char *filePath) {
    SSP_PLAYLISTITEM *item = playlistitem_create();
	item->id = playlist->nextId++;
    item->filePath = copystr((char *) item->filePath, filePath);
    vector_add(playlist->items, item);

    return SSP_OK;
}

SSP_ERROR playlist_insertItemAt(SSP_PLAYLIST *playlist, char* filePath, int index) {
    SSP_PLAYLISTITEM *item = playlistitem_create();
    item->filePath = malloc(strlen(filePath));
	item->id = playlist->nextId++;
    item->filePath = copystr((char *) item->filePath, filePath);
    vector_insert(playlist->items, index, item);

    return SSP_OK;
}

SSP_ERROR playlist_removeItemAt(SSP_PLAYLIST *playlist, int index) {
    SSP_PLAYLISTITEM* item = vector_get(playlist->items, index);
    playlistitem_free(item);
    vector_delete(playlist->items, index); // this reorders the whole array
    return SSP_OK;
}

SSP_ERROR playlist_clear(SSP_PLAYLIST *playlist) {
    log_text("playlist_clear\n");
    if(playlist->items != NULL) {
        for(int a = 0; a < playlist_getCount(playlist); a++) {
            playlistitem_free(playlist_getItemAt(playlist, a));
        }
        
        vector_free(playlist->items);
        free(playlist->items);
        playlist->items = NULL;
    }
    
    // Initialize vector
    playlist->items = malloc(sizeof(vector));
    vector_init(playlist->items);
    
    return SSP_OK;
}

SSP_PLAYLISTITEM* playlist_getItemAt(SSP_PLAYLIST *playlist, int index) {
    return vector_get(playlist->items, index);
}

SSP_PLAYLISTITEM* playlist_getItemFromId(SSP_PLAYLIST *playlist, int id) {
	for (int a = 0; a < playlist_getCount(playlist); a++) {
		SSP_PLAYLISTITEM* item = playlist_getItemAt(playlist, a);
		if (item->id == id) {
			return item;
		}
	}

	return NULL;
}

SSP_PLAYLISTITEM* playlist_getCurrentItem(SSP_PLAYLIST *playlist) {
    return playlist_getItemAt(playlist, playlist->currentIndex);
}

SSP_PLAYLISTITEM* playlist_getCurrentMixerItem(SSP_PLAYLIST *playlist) {
    return playlist_getItemAt(playlist, playlist->currentMixerIndex);
}

int playlist_getIndexFromId(SSP_PLAYLIST *playlist, int id) {
	for (int a = 0; a < playlist_getCount(playlist); a++) {
		SSP_PLAYLISTITEM* item = playlist_getItemAt(playlist, a);
		if (item->id == id) {
			return a;
		}
	}

	return -1;
}

int playlist_getCount(SSP_PLAYLIST *playlist) {
    return vector_total(playlist->items);
}

