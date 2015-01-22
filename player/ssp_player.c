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
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_eqpreset.h"
#include "ssp_playhead.h"
#include "ssp_bass.h"
#include "ssp_structs.h"
#include "ssp_privatestructs.h"
#include "bassmix.h"

#pragma mark Initialization

SSP_PLAYER* player_create() {
    SSP_PLAYER* player = malloc(sizeof(SSP_PLAYER));
    player->playlist = playlist_create();
    player->eqPreset = eqpreset_create();
    player->playhead = playhead_create();
    player->device = malloc(sizeof(SSP_DEVICE));
    player->mixer = malloc(sizeof(SSP_MIXER));
    player->channels = malloc(sizeof(SSP_PLAYER_CHANNELS));
    player->loop = NULL;
    player->marker = NULL;
    return player;
}

void player_free(SSP_PLAYER* player) {
    if(player->playlist) {
        playlist_free(player->playlist);
        free(player->playlist);
        player->playlist = NULL;
    }
    if(player->eqPreset) {
        eqpreset_free(player->eqPreset);
        free(player->eqPreset);
        player->eqPreset = NULL;
    }
    if(player->playhead) {
        playhead_free(player->playhead);
        free(player->playhead);
        player->playhead = NULL;
    }
    if(player->device) {
        free(player->device);
        player->device = NULL;
    }
    if(player->mixer) {
        free(player->mixer);
        player->mixer = NULL;
    }
    if(player->channels) {
        free(player->channels);
        player->channels = NULL;
    }
    if(player->loop) {
        free(player->loop);
        player->loop = NULL;
    }
    if(player->marker) {
        free(player->marker);
        player->marker = NULL;
    }
}

SSP_ERROR player_init(SSP_PLAYER* player, int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    // TODO: validate input

    // Set mixer properties
    player->mixer->sampleRate = sampleRate;
    player->mixer->bufferSize = bufferSize;
    player->mixer->updatePeriod = updatePeriod;
    player->mixer->useFloatingPoint = useFloatingPoint;

    // Reset playhead
    playhead_reset(player->playhead);

    SSP_ERROR error = bass_init(device, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
    return error;
}

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

//    if (!IsPaused)
//    {
//        Base.Pause();
//        IsPaused = true;
//    }
//    else
//    {
//        Base.Start();
//        IsPaused = false;
//        SetPosition(_positionAfterUnpause);
//    }

    if(player->playhead->isPaused) {
        bass_pause();
        player->playhead->isPaused = true;
    } else {
        bass_start();
        player->playhead->isPaused = false;
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

#pragma mark Seeking

uint64_t player_getPosition(SSP_PLAYER* player) {
    return bass_getPosition(player->channels->mixerChannel);
}

SSP_ERROR player_setPosition(SSP_PLAYER* player, uint64_t position) {
    SSP_ERROR error;
    bool success;

    if(player->playhead->isPaused) {
//        _positionAfterUnpause = bytes;
//        return;
    }

    if(player->playhead->isPlayingLoop) {
//        // If the new position is outside the current loop, stop the loop playback
//        var startPosition = Loop.GetStartSegment();
//        var endPosition = Loop.GetEndSegment();
//        if (bytes < startPosition.PositionBytes || bytes >= endPosition.PositionBytes)
//        {
//            StopLoop();
//        }
    }

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    //u_int64_t length = bass_getLength(<#(uint32_t)handle#>)

//    // Get as much data available before locking channel
//    RemoveSyncCallbacks();
//    long length = Playlist.CurrentItem.Channel.GetLength();

    success = BASS_ChannelLock(player->channels->mixerChannel, true);
    if(!success) {
        return bass_getError("BASS_ChannelLock");
    }

    player->playhead->isSettingPosition = true;
//    _positionOffset = bytes;
//
//    // Divide by 1.5 (I don't really know why, but this works for 48000Hz and 96000Hz. Maybe a bug in BASS with FLAC files?)
//    if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.CurrentItem.AudioFile.SampleRate > 44100)
//        bytes = (long)((float)bytes / 1.5f);
//
//    _mixerChannel.Stop();
    success = BASS_ChannelStop(player->channels->mixerChannel);
    if(!success) {
        return bass_getError("BASS_ChannelStop");
    }

    // Flush buffer
    error = bass_setPosition(currentItem->channel, 0);
    if(error != SSP_OK) {
        return error;
    }
    error = bass_setPosition(player->channels->fxChannel, 0);
    if(error != SSP_OK) {
        return error;
    }
    error = bass_setMixerPosition(player->channels->mixerChannel, 0);
    if(error != SSP_OK) {
        return error;
    }

    // Calculate position for floating point
    uint64_t bytesPosition = position;
    if (player->mixer->useFloatingPoint)
        bytesPosition *= 2;

    // Set position for decode channel
    error = bass_setPosition(currentItem->channel, bytesPosition);
    if(error != SSP_OK) {
        return error;
    }

    player_setSyncCallback(player, currentItem->length - bytesPosition);

    if(!player->playhead->isPaused) {
        success = BASS_ChannelPlay(player->channels->mixerChannel, false);
        if(!success) {
            return bass_getError("BASS_ChannelPlay");
        }
    }

    success = BASS_ChannelLock(player->channels->mixerChannel, false);
    if(!success) {
        return bass_getError("BASS_ChannelLock");
    }

    player->playhead->isSettingPosition = false;

    return SSP_OK;
}

