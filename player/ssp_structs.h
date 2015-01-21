//
//  structs.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef player_structs_h
#define player_structs_h

#include <stdbool.h>

typedef enum {SSP_PLAYER_STATE_UNKNOWN, SSP_PLAYER_STATE_INITIALIZED, SSP_PLAYER_STATE_STOPPED, SSP_PLAYER_STATE_PLAYING, SSP_PLAYER_STATE_PAUSED} ssp_player_state_t;
typedef enum {SSP_PLAYER_REPEAT_OFF, SSP_PLAYER_REPEAT_PLAYLIST, SSP_PLAYER_REPEAT_SONG} ssp_player_repeat_t;

typedef struct {
    char* name;
    bool isInitialized;
} SSP_DEVICE;

typedef struct {
    int sampleRate;
    int bufferSize;
    int updatePeriod;
    bool useFloatingPoint;
} SSP_MIXER;

typedef struct {
    float volume; // should be merged with mixer?
    bool isPlaying;
    bool isPlayingLoop;
    bool isPaused;
    bool isShuffleEnabled;
    bool isSettingPosition;
    ssp_player_state_t stateType;
    ssp_player_repeat_t repeatType;
    float timeShifting;
    int pitchShifting;
} SSP_PLAYHEAD;

typedef struct {
    float center;
    char* label;
    float bandwidth;
    float gain;
    float q;
} SSP_EQPRESETBAND;

typedef struct {
    char* name;
    SSP_EQPRESETBAND bands[18];
} SSP_EQPRESET;

typedef struct {
    char* name;
    long position;
} SSP_MARKER;

typedef struct {
    char* name;
    long startPosition;
    long endPosition;
} SSP_LOOP;

typedef struct {
//    char* filePath;
    // consider using a static array
    char filePath[1024];
    float sampleRate;
    int numberOfChannels;
} SSP_AUDIOFILE;



#endif
