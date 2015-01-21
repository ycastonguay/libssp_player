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
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "vector.h"

#pragma mark Playlist Items

SSP_PLAYLISTITEM* playlistitem_create() {
    SSP_PLAYLISTITEM* item = malloc(sizeof(SSP_PLAYLISTITEM));
    item->audioFile = malloc(sizeof(SSP_AUDIOFILE));
    return item;
}

void playlistitem_free(SSP_PLAYLISTITEM *item) {
    if(item->audioFile) {
        free(item->audioFile);
        item->audioFile = NULL;
    }
}

#pragma mark Playlist

SSP_PLAYLIST* playlist_create() {
    SSP_PLAYLIST* playlist = malloc(sizeof(SSP_PLAYLIST));
    playlist->items = malloc(sizeof(vector));
    vector_init(playlist->items);

    return playlist;
}

void playlist_free(SSP_PLAYLIST *playlist) {
    if(playlist->items) {
        vector_free(playlist->items);
        free(playlist->items);
        playlist->items = NULL;
    }
}

int playlist_addItem(SSP_PLAYLIST *playlist, char *filePath) {
    SSP_AUDIOFILE *audioFile = malloc(sizeof(SSP_AUDIOFILE));
//    audioFile->filePath = malloc(sizeof(filePath));
//    strncpy(audioFile->filePath, filePath, sizeof(filePath));

    SSP_PLAYLISTITEM *item = playlistitem_create();
    vector_add(playlist->items, item);

    // test
    int total = vector_total(playlist->items);
    SSP_PLAYLISTITEM *firstItem = vector_get(playlist->items, 0);
    SSP_PLAYLISTITEM *secondItem = vector_get(playlist->items, 1);
    SSP_PLAYLISTITEM *thirdItem = vector_get(playlist->items, 2);
    SSP_PLAYLISTITEM *lastItem = vector_get(playlist->items, vector_total(playlist->items)-1);

    return SSP_ERROR_OK;
}

int playlist_insertItemAt(SSP_PLAYLIST *playlist, char* filePath, int index) {
    // TODO: we need to copy items... unless we do a struct with a pointer to the next item
    return SSP_ERROR_OK;
}

int playlist_removeItemAt(SSP_PLAYLIST *playlist, int index) {
    SSP_PLAYLISTITEM* item = vector_get(playlist->items, index);
    playlistitem_free(item);
    vector_delete(playlist->items, index); // this reorders the whole array
    return SSP_ERROR_OK;
}

int playlist_removeItems(SSP_PLAYLIST *playlist) {
    // TODO: Free each playlist item with a for loop
    //vector_free(playlist->items);
    //vector_init(playlist->items);
    return SSP_ERROR_OK;
}

SSP_PLAYLISTITEM* playlist_getItemAt(SSP_PLAYLIST *playlist, int index) {
    return vector_get(playlist->items, index);
}

int playlist_getCount(SSP_PLAYLIST *playlist) {
    return vector_total(playlist->items);
}
