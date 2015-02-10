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
    //const char* str;
    char str[32];
    uint64_t bytes;
    uint64_t ms;
    uint64_t samples;
} SSP_POSITION;

typedef struct {
    const char* name;
    const char* url;
    const char* password;
    int bitrate;
} SSP_CAST_SERVER;

typedef struct {
    const char* name;
    int deviceId;
    bool isInitialized;
} SSP_DEVICE;

typedef struct {
    int sampleRate;
    int bufferSize;
    int updatePeriod;
    bool useFloatingPoint;
} SSP_MIXER;

typedef struct {
    float center;
    char label[128];
    float bandwidth;
    float gain;
    float q;
} SSP_EQPRESETBAND;

typedef struct {
    char id[38];
    char name[128];
//    const char* id;
//    const char* name;
    SSP_EQPRESETBAND bands[18];
} SSP_EQPRESET;

// Could be simply startPosition and endPosition
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
    int bitsPerSample;
    uint32_t channel;
    uint64_t length;
} SSP_PLAYLISTITEM;

#endif
