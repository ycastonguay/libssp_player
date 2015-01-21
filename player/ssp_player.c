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

SSP_ERROR player_init(SSP_PLAYER* player, int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // TODO: validate input
    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    // Set default sspPlayer properties
    playhead_reset(player->playhead);

    bass_init(device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return SSP_ERROR_OK;
}

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

SSP_ERROR player_previous(SSP_PLAYER* player) {
    return SSP_ERROR_OK;
}

SSP_ERROR player_next(SSP_PLAYER* player) {
    return SSP_ERROR_OK;
}

SSP_ERROR player_goTo(SSP_PLAYER* player, int index) {
    return SSP_ERROR_OK;
}
