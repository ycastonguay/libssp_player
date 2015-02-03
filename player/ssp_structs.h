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

#ifndef player_structs_h
#define player_structs_h

#include <stdbool.h>
#include <stdint.h>
#include "ssp_callbacks.h"

typedef struct {
    const char* str;
    uint64_t bytes;
    uint64_t ms;
    uint64_t samples;
} SSP_POSITION;

typedef struct {
    const char* name;
    int deviceId;
    int test;
    bool isInitialized;
} SSP_DEVICE;

typedef struct {
    int sampleRate;
    int bufferSize;
    int updatePeriod;
    bool useFloatingPoint;
} SSP_MIXER;

typedef struct {
    // get
    bool isPlayingLoop;
    bool isShuffleEnabled;
    bool isSettingPosition;
    bool isEQEnabled;
    ssp_player_state_t state;

    // get/set
    ssp_player_repeat_t repeatType;
    float volume; // should be merged with mixer?
    float timeShifting;
    int pitchShifting;

    // temp (TODO: should this be part of playhead?)
    uint64_t positionAfterUnpause;

    // should be private
    // used for calculating the position offset when a song changes
    uint64_t positionOffset;
} SSP_PLAYHEAD;

typedef struct {
    float center;
    const char* label;
    float bandwidth;
    float gain;
    float q;
} SSP_EQPRESETBAND;

typedef struct {
    const char* name;
    SSP_EQPRESETBAND bands[18];
} SSP_EQPRESET;

typedef struct {
    const char* name;
    long position;
} SSP_MARKER;

typedef struct {
    const char* name;
    uint64_t startPosition;
    uint64_t endPosition;
} SSP_LOOP;

typedef struct {
    //char filePath[1024]; // consider using a static array
    bool isLoaded;
    const char* filePath;
    int sampleRate;
    int numberOfChannels;
    uint32_t channel;
    uint64_t length;
    uint64_t test;
} SSP_PLAYLISTITEM;

typedef struct {
    void* items;
    const char* name;
    int currentIndex;
    int currentMixerIndex;

    void* callbackPlaylistIndexChangedUser;
    player_playlistindexchanged_cb callbackPlaylistIndexChanged;

    void* callbackPlaylistEndedUser;
    player_playlistended_cb callbackPlaylistEnded;
} SSP_PLAYLIST;

#endif
