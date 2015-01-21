//
//  ssp_player.c
//  ssp_player
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_structs.h"
#include "ssp_eqpreset.h"
#include "ssp_playhead.h"
#include "ssp_privatestructs.h"
#include "ssp_bass.h"

//static SSP_PLAYER* sspPlayer; // static makes it private to this file

// TODO: Maybe put all public methods (i.e. SSP_*) in a different file than ssp_player.c?

#pragma mark Initialization

SSP_PLAYER* player_create() {
    SSP_PLAYER* player = malloc(sizeof(SSP_PLAYER));
    player->playlist = playlist_create();
    player->eqPreset = eqpreset_create();
    player->playhead = playhead_create();
    player->device = malloc(sizeof(SSP_DEVICE));
    player->mixer = malloc(sizeof(SSP_MIXER));
    player->loop = NULL;
    player->marker = NULL;
    return player;
}

void player_free(SSP_PLAYER* player) {
    if(player->playlist) {
        playlist_free(player->playlist);
        free(player->playlist);
        player->playlist = NULL;
    }
    if(player->eqPreset) {
        eqpreset_free(player->eqPreset);
        free(player->eqPreset);
        player->eqPreset = NULL;
    }
    if(player->playhead) {
        playhead_free(player->playhead);
        free(player->playhead);
        player->playhead = NULL;
    }
    if(player->device) {
        free(player->device);
        player->device = NULL;
    }
    if(player->mixer) {
        free(player->mixer);
        player->mixer = NULL;
    }
    if(player->loop) {
        free(player->loop);
        player->loop = NULL;
    }
    if(player->marker) {
        free(player->marker);
        player->marker = NULL;
    }
}

void player_init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    
    if(!sspPlayer) {
        sspPlayer = player_create();
    } else {
        // TODO: Add reset?
    }

    sspPlayer->mixer->sampleRate = sampleRate;
    sspPlayer->mixer->bufferSize = bufferSize;
    sspPlayer->mixer->updatePeriod = updatePeriod;
    sspPlayer->mixer->useFloatingPoint = useFloatingPoint;

    // Set default sspPlayer properties
    playhead_reset(sspPlayer->playhead);

    bass_init(device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
}

int SSP_Init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // TODO: validate input

    player_init(device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return SSP_ERROR_OK;
}

#pragma mark Device

//SSP_DEVICE SSP_GetDevice() {
//    //return sspPlayer.device;
//    return NULL;
//}

#pragma mark Playback

SSP_ERROR player_pause(SSP_PLAYER* player) {
    return SSP_ERROR_OK;
}

SSP_ERROR player_stop(SSP_PLAYER* player) {
    return SSP_ERROR_OK;
}

SSP_ERROR player_play(SSP_PLAYER* player) {

    if(player->playhead->isPlaying) {
        if(player->playhead->isPlayingLoop) {
            // TODO: stop loop
        }

        player_stop(player);
    }

    int channelsToLoad = playlist_getCount(player->playlist) - player->playlist->currentIndex;
    if(channelsToLoad > 2)
        channelsToLoad = 2;

    if(channelsToLoad == 0) {
        return SSP_ERROR_UNKNOWN;
    }

    //sspPlayer->

    return SSP_ERROR_OK;
}

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
    return SSP_ERROR_OK;
}

SSP_ERROR SSP_Next() {
    return SSP_ERROR_OK;
}

SSP_ERROR SSP_GoTo(int index) {
    return SSP_ERROR_OK;
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