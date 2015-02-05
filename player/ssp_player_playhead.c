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

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../bass/bassmix.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_log.h"
#include "ssp_structs.h"
#include "ssp_privatestructs.h"

bool player_getIsShuffle(SSP_PLAYER* player) {
    return player->playhead->isShuffleEnabled;
}

void player_setIsShuffle(SSP_PLAYER* player, bool shuffle) {
    player->playhead->isShuffleEnabled = shuffle;
}

ssp_player_repeat_t player_getRepeatType(SSP_PLAYER* player) {
    return player->playhead->repeatType;
}

void player_setRepeatType(SSP_PLAYER* player, ssp_player_repeat_t repeat) {
    player->playhead->repeatType = repeat;
    // TODO: Finish this
}

float player_getVolume(SSP_PLAYER* player) {
    return player->playhead->volume;
}

void player_setVolume(SSP_PLAYER* player, float volume) {
    player->playhead->volume = volume;
    // TODO: Finish this
}

float player_getTimeShifting(SSP_PLAYER* player) {
    return player->playhead->timeShifting;
}

void player_setTimeShifting(SSP_PLAYER* player, float timeShifting) {
    player->playhead->timeShifting = timeShifting;
    // TODO: Finish this
}

int player_getPitchShifting(SSP_PLAYER* player) {
    return player->playhead->pitchShifting;
}

void player_setPitchShifting(SSP_PLAYER* player, int pitchShifting) {
    player->playhead->pitchShifting = pitchShifting;
    // TODO: Finish this
}
