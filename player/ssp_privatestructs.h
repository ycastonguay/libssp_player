//
//  ssp_privatestructs.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 15-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef player_ssp_privatestructs____FILEEXTENSION___
#define player_ssp_privatestructs____FILEEXTENSION___

#import "bass.h"
#import "ssp_structs.h"

typedef struct {
    HCHANNEL streamChannel;
    HCHANNEL fxChannel;
    STREAMPROC* streamProc;
    SYNCPROC* syncProc;
} SSP_BASS_CHANNELS;

typedef struct {
    SSP_AUDIOFILE* audioFile;
    HCHANNEL channel;
    long length;
    bool isLoaded;
} SSP_PLAYLISTITEM;

typedef struct {
    void* items;
    char* name;
    int currentIndex;
    int currentMixerIndex;
} SSP_PLAYLIST;

typedef struct {

    // private
    SSP_BASS_CHANNELS* bassChannels;

    // getters
    // what happens if someone goes getDevice() and changes the properties?
    // we can't allow that, so do we need to copy the object?
    SSP_DEVICE* device;
    SSP_PLAYLIST* playlist;
    SSP_MIXER* mixer;
    SSP_PLAYHEAD* playhead;

    // getters/setters
    SSP_EQPRESET* eqPreset;
    SSP_LOOP* loop;
    SSP_MARKER* marker;
} SSP_PLAYER;

#endif
