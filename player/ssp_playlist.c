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
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_log.h"

#pragma mark Playlist Items

SSP_PLAYLISTITEM* playlistitem_create() {
    SSP_PLAYLISTITEM* item = malloc(sizeof(SSP_PLAYLISTITEM));
    playlistitem_reset(item);
    return item;
}

void playlistitem_free(SSP_PLAYLISTITEM *item) {
    if(item->audioFile) {
        free(item->audioFile);
        item->audioFile = NULL;
    }
}

void playlistitem_reset(SSP_PLAYLISTITEM *item) {
    item->audioFile = malloc(sizeof(SSP_AUDIOFILE));
    item->channel = 0;
    item->isLoaded = false;
    item->length = 0;
}

void playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint) {
    // refresh audiofile metadata (?)
    // check if channel exists, if true, then dispose (?)
    log_textf("playlistitem_load -- Creating stream for decoding (filePath: %s)...\n", item->audioFile->filePath);
    item->channel = bass_createDecodeStream(item->audioFile->filePath, useFloatingPoint);
    log_text("playlistitem_load -- Getting length...\n");
    item->length = bass_getLength(item->channel);
    log_text("playlistitem_load -- Setting flags...\n");
    item->isLoaded = true;
    item->test = 777;
}

SSP_ERROR playlist_disposeChannels(SSP_PLAYLIST *playlist) {
    SSP_ERROR error;
    if(playlist->items != NULL) {
        for(int a = 0; a < playlist_getCount(playlist); a++) {
            error = playlistitem_disposeChannel(playlist_getItemAt(playlist, a));
            if(error != SSP_OK) {
                return error;
            }
        }
    }

    return SSP_OK;
}

#pragma mark Playlist

SSP_PLAYLIST* playlist_create() {
    SSP_PLAYLIST* playlist = malloc(sizeof(SSP_PLAYLIST));
    playlist->items = malloc(sizeof(vector));
    vector_init(playlist->items);

    playlist->currentIndex = 0;
    playlist->currentMixerIndex = 0;
    playlist->name = NULL;
    playlist->callbackPlaylistIndexChanged = NULL;
    playlist->callbackPlaylistIndexChangedUser = NULL;

    return playlist;
}

void playlist_free(SSP_PLAYLIST *playlist) {
    if(playlist->items) {
        vector_free(playlist->items);
        free(playlist->items);
        playlist->items = NULL;
    }
    if(playlist->name) {
        free(playlist->name);
        playlist->name = NULL;
    }
    if(playlist->callbackPlaylistIndexChanged) {
        //free(playlist->callbackPlaylistIndexChanged);
        playlist->callbackPlaylistIndexChanged = NULL;
    }
    playlist->callbackPlaylistIndexChangedUser = NULL;
}

SSP_ERROR playlistitem_disposeChannel(SSP_PLAYLISTITEM *item) {
    bool success = BASS_ChannelStop(item->channel);
    if(!success) {
        return bass_getError("playlistitem_disposeChannel");
    }

    success = BASS_StreamFree(item->channel);
    if(!success) {
        return bass_getError("playlistitem_disposeChannel");
    }

    playlistitem_reset(item);

    return SSP_OK;
}

int playlist_addItem(SSP_PLAYLIST *playlist, char *filePath) {
    SSP_AUDIOFILE *audioFile = malloc(sizeof(SSP_AUDIOFILE));
    audioFile->filePath = malloc(strlen(filePath));
    strcpy(audioFile->filePath, filePath);

    SSP_PLAYLISTITEM *item = playlistitem_create();
    vector_add(playlist->items, item);
    item->audioFile = audioFile;

    // test
    int total = vector_total(playlist->items);
    SSP_PLAYLISTITEM *firstItem = vector_get(playlist->items, 0);
    SSP_PLAYLISTITEM *secondItem = vector_get(playlist->items, 1);
    SSP_PLAYLISTITEM *thirdItem = vector_get(playlist->items, 2);
    SSP_PLAYLISTITEM *lastItem = vector_get(playlist->items, vector_total(playlist->items)-1);

    return SSP_OK;
}

int playlist_insertItemAt(SSP_PLAYLIST *playlist, char* filePath, int index) {
    // TODO: we need to copy items... unless we do a struct with a pointer to the next item
    return SSP_OK;
}

int playlist_removeItemAt(SSP_PLAYLIST *playlist, int index) {
    SSP_PLAYLISTITEM* item = vector_get(playlist->items, index);
    playlistitem_free(item);
    vector_delete(playlist->items, index); // this reorders the whole array
    return SSP_OK;
}

int playlist_clear(SSP_PLAYLIST *playlist) {
    if(playlist->items != NULL) {
        // Clear all items
        for(int a = 0; a < playlist_getCount(playlist); a++) {
            playlistitem_free(playlist_getItemAt(playlist, a));
        }
        
        // Clear vector
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

SSP_PLAYLISTITEM* playlist_getCurrentItem(SSP_PLAYLIST *playlist) {
    return playlist_getItemAt(playlist, playlist->currentIndex);
}

SSP_PLAYLISTITEM* playlist_getCurrentMixerItem(SSP_PLAYLIST *playlist) {
    return playlist_getItemAt(playlist, playlist->currentMixerIndex);
}

int playlist_getCount(SSP_PLAYLIST *playlist) {
    return vector_total(playlist->items);
}

