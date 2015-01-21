//
//  ssp_public.c
//  player
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include "ssp_public.h"
#include "ssp_privatestructs.h"
#include "ssp_errors.h"
#include "ssp_playlist.h"
#include "ssp_player.h"

static SSP_PLAYER* sspPlayer; // static makes it private to this file

//int SSP_GetBufferSize() {
//    return 10;
//}

#pragma mark Initialization

int SSP_Init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {

    // Create player if not created yet
    if(sspPlayer == NULL) {
        sspPlayer = player_create();
    }

    player_init(sspPlayer, device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return SSP_ERROR_OK;
}

#pragma mark Device

SSP_DEVICE* SSP_GetDevice() {
    //return sspPlayer.device;
    return NULL;
}

#pragma mark Playback

SSP_ERROR SSP_Play() {
    return player_play(sspPlayer);
}

SSP_ERROR SSP_Pause() {
    return player_pause(sspPlayer);
}

SSP_ERROR SSP_Stop() {
    return player_stop(sspPlayer);
}

SSP_ERROR SSP_Previous() {
    return player_previous(sspPlayer);
}

SSP_ERROR SSP_Next() {
    return player_next(sspPlayer);
}

SSP_ERROR SSP_GoTo(int index) {
    return player_goTo(sspPlayer, index);
}

#pragma mark Playlist

int SSP_Playlist_AddItem(char* filePath) {
    return playlist_addItem(sspPlayer->playlist, filePath);
}

int SSP_Playlist_InsertItemAt(char* filePath, int index) {
    return playlist_insertItemAt(sspPlayer->playlist, filePath, index);
}

int SSP_Playlist_RemoveItemAt(int index) {
    return playlist_removeItemAt(sspPlayer->playlist, index);
}

int SSP_Playlist_RemoveItems() {
    return playlist_removeItems(sspPlayer->playlist);
}

SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index) {
    return playlist_getItemAt(sspPlayer->playlist, index);
}

int SSP_Playlist_GetCount() {
    return playlist_getCount(sspPlayer->playlist);
}

int SSP_Playlist_GetCurrentIndex() {
    return sspPlayer->playlist->currentIndex;
}

#pragma mark EQ Presets

SSP_EQPRESET* SSP_GetEQPreset() {
    SSP_EQPRESET* preset = malloc(sizeof(SSP_EQPRESET));
    memcpy(preset, sspPlayer->eqPreset, sizeof(SSP_EQPRESET));
    return preset;
}