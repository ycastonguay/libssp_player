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

#ifndef player_callbacks_h
#define player_callbacks_h

#include "ssp_enums.h"

typedef void (*player_log_cb)(void *user, const char* str);
typedef void (*player_statechanged_cb)(void *user, ssp_player_state_t state);
typedef void (*player_playlistindexchanged_cb)(void *user);
typedef void (*player_playlistended_cb)(void *user);
typedef void (*player_loopplaybackstarted_cb)(void *user);
typedef void (*player_loopplaybackstopped_cb)(void *user);
typedef void (*player_audiointerrupted_cb)(void *user);
typedef void (*player_bpmdetected_cb)(void *user, float bpm);

#endif
