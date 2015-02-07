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

#ifndef player_ssp_player____FILEEXTENSION___
#define player_ssp_player____FILEEXTENSION___

#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_callbacks.h"
#include "ssp_privatestructs.h"

SSP_PLAYER* player_create();
SSP_ERROR player_free(SSP_PLAYER* sspPlayer);

SSP_ERROR player_init(SSP_PLAYER* player);
SSP_ERROR player_initDevice(SSP_PLAYER* player, int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
SSP_ERROR player_freeDevice(SSP_PLAYER* player);
SSP_ERROR player_loadPlugins(SSP_PLAYER* player);
SSP_ERROR player_freePlugins(SSP_PLAYER* player);
SSP_ERROR player_getBassVersions();

void player_updateState(SSP_PLAYER* player, ssp_player_state_t state);

// Playback
SSP_ERROR player_pause(SSP_PLAYER* player);
SSP_ERROR player_stop(SSP_PLAYER* player);
SSP_ERROR player_play(SSP_PLAYER* player);
SSP_ERROR player_previous(SSP_PLAYER* player);
SSP_ERROR player_next(SSP_PLAYER* player);
SSP_ERROR player_goTo(SSP_PLAYER* player, int index);

// Playhead
bool player_getIsShuffle(SSP_PLAYER* player);
void player_setIsShuffle(SSP_PLAYER* player, bool shuffle);

ssp_player_repeat_t player_getRepeatType(SSP_PLAYER* player);
void player_setRepeatType(SSP_PLAYER* player, ssp_player_repeat_t repeat);

float player_getVolume(SSP_PLAYER* player);
void player_setVolume(SSP_PLAYER* player, float volume);

float player_getTimeShifting(SSP_PLAYER* player);
void player_setTimeShifting(SSP_PLAYER* player, float timeShifting);

int player_getPitchShifting(SSP_PLAYER* player);
void player_setPitchShifting(SSP_PLAYER* player, int pitchShifting);

// Position
uint64_t player_getPosition(SSP_PLAYER* player);
void player_getPositionNew(SSP_PLAYER* player, SSP_POSITION* position);
SSP_ERROR player_setPosition(SSP_PLAYER* player, uint64_t position);

// Data
int player_getMixerData(SSP_PLAYER* player, void* buffer, int length);

// EQ
SSP_ERROR player_createEQStage(SSP_PLAYER* player);
SSP_ERROR player_removeEQStage(SSP_PLAYER* player);
SSP_ERROR player_updateEQBand(SSP_PLAYER* player, int band, float gain);
SSP_ERROR player_applyEQ(SSP_PLAYER* player, SSP_EQPRESET* eqpreset);
SSP_ERROR player_resetEQ(SSP_PLAYER* player);
SSP_ERROR player_enableEQ(SSP_PLAYER* player, bool enabled);
SSP_ERROR player_normalizeEQ(SSP_PLAYER* player);

// Callbacks
SSP_ERROR player_setSyncCallback(SSP_PLAYER* player, uint64_t position);
SSP_ERROR player_removeSyncCallbacks(SSP_PLAYER* player);

void player_setPlaylistIndexChangedCallback(SSP_PLAYER* player, player_playlistindexchanged_cb cb, void* user);
void player_removePlaylistIndexChangedCallback(SSP_PLAYER* player);

void player_setPlaylistEndedCallback(SSP_PLAYER* player, player_playlistended_cb cb, void* user);
void player_removePlaylistEndedCallback(SSP_PLAYER* player);

void player_setStateChangedCallback(SSP_PLAYER* player, player_statechanged_cb cb, void* user);
void player_removeStateChangedCallback(SSP_PLAYER* player);

#endif
