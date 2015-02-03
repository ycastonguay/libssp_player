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
    playhead->isPlayingLoop = false;
    playhead->isSettingPosition = false;
    playhead->isShuffleEnabled = false;
    playhead->isEQEnabled = false;
    playhead->pitchShifting = 0;
    playhead->timeShifting = 1;
    playhead->volume = 1;
    playhead->repeatType = SSP_PLAYER_REPEAT_OFF;
    playhead->state = SSP_PLAYER_STATE_UNKNOWN;
    playhead->positionOffset = 0;
    playhead->positionAfterUnpause = 0;
}