//
//  ssp_playhead.c
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-20.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <stdlib.h>
#include "ssp_playhead.h"
#include "ssp_structs.h"

SSP_PLAYHEAD* playhead_create() {
    SSP_PLAYHEAD* playhead = malloc(sizeof(SSP_PLAYHEAD));
    return playhead;
}

void playhead_free(SSP_PLAYHEAD *playhead) {
    // should be empty and keep no pointers, since this is a state class
}

void playhead_reset(SSP_PLAYHEAD* playhead) {
    playhead->isPlaying = false;
    playhead->isPlayingLoop = false;
    playhead->isPaused = false;
    playhead->isSettingPosition = false;
    playhead->isShuffleEnabled = false;
    playhead->pitchShifting = 0;
    playhead->timeShifting = 1;
    playhead->volume = 1;
    playhead->repeatType = SSP_PLAYER_REPEAT_OFF;
    playhead->stateType = SSP_PLAYER_STATE_UNKNOWN;
}