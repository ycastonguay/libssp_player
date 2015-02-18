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
#include "ssp_privatestructs.h"

void player_setPlaylistIndexChangedCallback(SSP_PLAYER* player, player_playlistindexchanged_cb cb, void *user) {
    player->playlist->callbackPlaylistIndexChanged = cb;
    player->playlist->callbackPlaylistIndexChangedUser = user;
}

void player_removePlaylistIndexChangedCallback(SSP_PLAYER* player) {
    player->playlist->callbackPlaylistIndexChanged = NULL;
    player->playlist->callbackPlaylistIndexChangedUser = NULL;
}

void player_setPlaylistEndedCallback(SSP_PLAYER* player, player_playlistended_cb cb, void* user) {
    player->playlist->callbackPlaylistEnded = cb;
    player->playlist->callbackPlaylistEndedUser = user;
}

void player_removePlaylistEndedCallback(SSP_PLAYER* player) {
    player->playlist->callbackPlaylistEnded = NULL;
    player->playlist->callbackPlaylistEndedUser = NULL;
}

void player_setStateChangedCallback(SSP_PLAYER* player, player_statechanged_cb cb, void* user) {
    player->callbackStateChanged = cb;
    player->callbackStateChangedUser = user;
}

void player_removeStateChangedCallback(SSP_PLAYER* player) {
    player->callbackStateChanged = NULL;
    player->callbackStateChangedUser = NULL;
}

void player_setLoopPlaybackStartedCallback(SSP_PLAYER* player, player_loopplaybackstarted_cb cb, void* user) {
    player->callbackLoopPlaybackStarted = cb;
    player->callbackLoopPlaybackStartedUser = user;
}

void player_removeLoopPlaybackStartedCallback(SSP_PLAYER* player) {
    player->callbackLoopPlaybackStarted = NULL;
    player->callbackLoopPlaybackStartedUser = NULL;
}

void player_setLoopPlaybackStoppedCallback(SSP_PLAYER* player, player_loopplaybackstopped_cb cb, void* user) {
    player->callbackLoopPlaybackStopped = cb;
    player->callbackLoopPlaybackStoppedUser = user;
}

void player_removeLoopPlaybackStoppedCallback(SSP_PLAYER* player) {
    player->callbackLoopPlaybackStopped = NULL;
    player->callbackLoopPlaybackStoppedUser = NULL;
}

void player_setAudioInterruptedCallback(SSP_PLAYER* player, player_audiointerrupted_cb cb, void* user) {
    player->callbackAudioInterrupted = cb;
    player->callbackAudioInterruptedUser = user;
}

void player_removeAudioInterruptedCallback(SSP_PLAYER* player) {
    player->callbackAudioInterrupted = NULL;
    player->callbackAudioInterruptedUser = NULL;
}

void player_setBPMDetectedCallback(SSP_PLAYER* player, player_bpmdetected_cb cb, void* user) {
    player->callbackBPMDetected = cb;
    player->callbackBPMDetectedUser = user;
}

void player_removeBPMDetectedCallback(SSP_PLAYER* player) {
    player->callbackBPMDetected = NULL;
    player->callbackBPMDetectedUser = NULL;
}
