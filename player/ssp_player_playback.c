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
//#include "ssp_player_playback.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_eqpreset.h"
#include "ssp_playhead.h"
#include "ssp_bass.h"
#include "ssp_structs.h"
#include "ssp_privatestructs.h"
#include "bassmix.h"

#pragma mark Callbacks

DWORD CALLBACK player_streamProc(HSTREAM handle, float *buffer, DWORD length, void *user) {

    SSP_PLAYER *player = (SSP_PLAYER*)user;
    SSP_PLAYLISTITEM *currentItem = playlist_getCurrentItem(player->playlist);

    //printf("player_streamProc - length: %d\n", length);

    int active = BASS_ChannelIsActive(currentItem->channel);
    if(active == BASS_ACTIVE_PLAYING) {
        DWORD data = BASS_ChannelGetData(currentItem->channel, buffer, length);
        printf("player_streamProc - length: %d - data: %d\n", length, data);
        return data;
    }
    else if(active == BASS_ACTIVE_STOPPED) {
        // Skip to next song
    }

    return BASS_STREAMPROC_END;
}

void CALLBACK player_testSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
}

SSP_ERROR player_setSyncCallback(SSP_PLAYER* player, uint64_t position) {
    int syncHandle = bass_setMixerSyncProc(player->channels->mixerChannel, position, player_testSyncProc);
    // TODO: Add to a list of sync procs for use later

    return SSP_OK;
}

#pragma mark Playback

SSP_ERROR player_pause(SSP_PLAYER* player) {
    if(player->playhead->isPaused) {
            bass_pause();
            player->playhead->isPaused = true;
        } else {
        bass_start();
        player->playhead->isPaused = false;
//        SetPosition(_positionAfterUnpause);
    }

    return SSP_OK;
}

SSP_ERROR player_stop(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_play(SSP_PLAYER* player) {

    SSP_ERROR error;

    printf("player_play\n");
    if(player->playhead->isPlaying) {
        if(player->playhead->isPlayingLoop) {
            // TODO: stop loop
        }

        player_stop(player);
    }

    printf("player_play - Getting current index and count...\n");
    int currentIndex = player->playlist->currentIndex;
    int count = playlist_getCount(player->playlist);

    int channelsToLoad = count - currentIndex;
    if(channelsToLoad > 2)
        channelsToLoad = 2;

    if(channelsToLoad == 0) {
        printf("player_play - ERROR: There are no channels to load!\n");
        return SSP_ERROR_UNKNOWN;
    }

    for(int a = currentIndex; a < currentIndex + channelsToLoad; a++) {
        printf("player_play - Loading playlist item %d...\n", a);
        SSP_PLAYLISTITEM* item = playlist_getItemAt(player->playlist, a);
        item->test = 666;
        playlistitem_load(item, player->mixer->useFloatingPoint);
        SSP_PLAYLISTITEM* item2 = playlist_getItemAt(player->playlist, a);
        int b = 0;
        //item->/
        //item->channel
    }

    // Default output driver (i.e. DirectSound)
    // TODO: How do we check for errors?
    printf("player_play - Setting stream channel and proc...\n");
    player->channels->streamProc = (STREAMPROC*)player_streamProc;

    // Prepare stream channel
    player->channels->streamChannel = bass_createMemoryStream(player->mixer->sampleRate, 2, player->mixer->useFloatingPoint, player->channels->streamProc, player);
    if(player->channels->streamChannel == 0) {
        return SSP_ERROR_UNKNOWN;
    }

    // Prepare FX channel (for pitch and time shifting)
    player->channels->fxChannel = bass_createStreamForTimeShifting(player->channels->streamChannel, true, player->mixer->useFloatingPoint);
    if(player->channels->fxChannel == 0) {
        return SSP_ERROR_UNKNOWN;
    }

    // Prepare mixer channel
    player->channels->mixerChannel = bass_createMixerStream(player->mixer->sampleRate, 2, false, player->mixer->useFloatingPoint);
    if(player->channels->mixerChannel == 0) {
        return SSP_ERROR_UNKNOWN;
    }

    // Add FX channel to mixer
    error = bass_addChannelToMixer(player->channels->mixerChannel, player->channels->fxChannel);
    if(error != SSP_OK) {
        return error;
    }

    // TODO: Add BPM callbacks here

    // set initial volume
    // add eq
    // if eq is bypassed, then reset it
    // set flags for repeat
    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    //uint64_t length = bass_getLength(currentItem->channel);

//    error = player_setSyncCallback(player, currentItem->length);
//    if(error != SSP_OK) {
//        return error;
//    }

    player->playhead->isPlaying = true;

    error = bass_start();
    if(error != SSP_OK) {
        return error;
    }

    error = bass_play(player->channels->mixerChannel, false);
    if(error != SSP_OK) {
        return error;
    }

    // invoke onplaylistindexchanged
    printf("player_play - Finished playback sequence!\n");

    return SSP_OK;
}

SSP_ERROR player_previous(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_next(SSP_PLAYER* player) {
    return SSP_OK;
}

SSP_ERROR player_goTo(SSP_PLAYER* player, int index) {
    return SSP_OK;
}
