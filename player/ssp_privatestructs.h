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

#import "bass.h"
#import "ssp_structs.h"

typedef struct {
    HCHANNEL streamChannel;
    HCHANNEL fxChannel;
    HCHANNEL mixerChannel;
    STREAMPROC* streamProc;
    SYNCPROC* syncProc;
    int syncProcHandles[100];
    int syncProcCount;
} SSP_PLAYER_CHANNELS;

typedef struct {
    // private
    SSP_PLAYER_CHANNELS* channels;

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
