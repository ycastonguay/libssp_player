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

#ifndef player_ssp_privatestructs____FILEEXTENSION___
#define player_ssp_privatestructs____FILEEXTENSION___

#include "../bass/bass.h"
#include "../bass/bassenc.h"
#include "ssp_structs.h"

typedef struct {
    HCHANNEL streamChannel;
    HCHANNEL fxChannel;
    HCHANNEL mixerChannel;

    HPLUGIN apePlugin;
	HPLUGIN aacPlugin;
	HPLUGIN alacPlugin;
	HPLUGIN flacPlugin;
	HPLUGIN mpcPlugin;
    HPLUGIN ttaPlugin;
	HPLUGIN wmaPlugin;
    HPLUGIN wvPlugin;

    HFX eqFX;

    HSYNC syncProcLoop;

    HENCODE encoder;

    STREAMPROC* streamProc;
    SYNCPROC* syncProc;

    void* syncProcHandles;
} SSP_PLAYER_HANDLES;

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

typedef struct {
    // get
    bool isPlayingLoop;
    ssp_player_state_t state;

    // get/set
    bool isEQEnabled;
    bool isShuffleEnabled;
    ssp_player_repeat_t repeatType;
    float volume;
    float timeShifting;
    int pitchShifting;

    // private
    bool isSettingPosition;
    uint64_t positionAfterUnpause;
    uint64_t positionOffset; // used for calculating the position offset when a song changes
} SSP_PLAYHEAD;

typedef struct {
    // get
    SSP_DEVICE* device;
    SSP_MIXER* mixer;

    // get/set
    SSP_EQPRESET* eqPreset;
    SSP_LOOP* loop;

    // private
    SSP_PLAYER_HANDLES* handles;
    SSP_PLAYLIST* playlist;
    SSP_PLAYHEAD* playhead;

    const char* pathForPlugins;

    player_statechanged_cb callbackStateChanged;
    void* callbackStateChangedUser;

    player_loopplaybackstarted_cb callbackLoopPlaybackStarted;
    void* callbackLoopPlaybackStartedUser;

    player_loopplaybackstopped_cb callbackLoopPlaybackStopped;
    void* callbackLoopPlaybackStoppedUser;

    player_audiointerrupted_cb callbackAudioInterrupted;
    void* callbackAudioInterruptedUser;

    player_bpmdetected_cb callbackBPMDetected;
    void* callbackBPMDetectedUser;
} SSP_PLAYER;

#endif
