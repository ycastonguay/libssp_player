//
//  playlist.c
//  sspPlayer
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_playlist.h"
#include "vector.h"
#include "ssp_bass.h"

#pragma mark Playlist Items

SSP_PLAYLISTITEM* playlistitem_create() {
    SSP_PLAYLISTITEM* item = malloc(sizeof(SSP_PLAYLISTITEM));
    item->audioFile = malloc(sizeof(SSP_AUDIOFILE));
    item->channel = 0;
    item->isLoaded = false;
    item->length = 0;
    return item;
}

void playlistitem_free(SSP_PLAYLISTITEM *item) {
    if(item->audioFile) {
        free(item->audioFile);
        item->audioFile = NULL;
    }
}

void playlistitem_load(SSP_PLAYLISTITEM *item, bool useFloatingPoint) {
    // refresh audiofile metadata (?)
    // check if channel exists, if true, then dispose (?)
    printf("playlistitem_load -- Creating stream for decoding (filePath: %s)...\n", item->audioFile->filePath);
    item->channel = bass_createDecodeStream(item->audioFile->filePath, useFloatingPoint);
    printf("playlistitem_load -- Getting length...\n");
    item->length = bass_getLength(item->channel);
    printf("playlistitem_load -- Setting flags...\n");
    item->isLoaded = true;
}

#pragma mark Playlist

SSP_PLAYLIST* playlist_create() {
    SSP_PLAYLIST* playlist = malloc(sizeof(SSP_PLAYLIST));
    playlist->items = malloc(sizeof(vector));
    vector_init(playlist->items);

    playlist->currentIndex = 0;
    playlist->currentMixerIndex = 0;
    playlist->name = NULL;

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

int playlist_removeItems(SSP_PLAYLIST *playlist) {
    // TODO: Free each playlist item with a for loop
    //vector_free(playlist->items);
    //vector_init(playlist->items);
    return SSP_OK;
}

SSP_PLAYLISTITEM* playlist_getItemAt(SSP_PLAYLIST *playlist, int index) {
    return vector_get(playlist->items, index);
}

int playlist_getCount(SSP_PLAYLIST *playlist) {
    return vector_total(playlist->items);
}

