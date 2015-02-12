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
#include "../bass/bassmix.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_log.h"
#include "ssp_playlistitem.h"

SSP_ERROR player_pause(SSP_PLAYER* player) {
    if(player->playhead->state == SSP_PLAYER_STATE_PLAYING) {
        bool success = BASS_Pause();
        if(!success) {
            bass_getError("BASS_Pause");
            return SSP_ERROR_PLAYBACK_PAUSE_FAILEDTOPAUSE;
        }
        player_updateState(player, SSP_PLAYER_STATE_PAUSED);
    }
    else {
        bool success = BASS_Start();
        if(!success) {
            bass_getError("BASS_Start");
            return SSP_ERROR_PLAYBACK_PAUSE_FAILEDTOSTART;
        }
        player_setPosition(player, player->playhead->positionAfterUnpause);
        player_updateState(player, SSP_PLAYER_STATE_PLAYING);
    }

    return SSP_OK;
}

SSP_ERROR player_stop(SSP_PLAYER* player) {
    // reset loop here
    //if(player->playhead->isEQEnabled) {
        player_removeEQStage(player);
    //}

    bool success = BASS_ChannelStop(player->handles->mixerChannel);
    if(!success) {
        return SSP_ERROR_PLAYBACK_STOP_FAILEDTOSTOPCHANNEL;
    }

    success = BASS_Stop();
    if(!success) {
        return SSP_ERROR_PLAYBACK_STOP_FAILEDTOSTOPCHANNEL;
    }

    SSP_ERROR error = player_removeSyncCallbacks(player);
    if(error != SSP_OK) {
        return SSP_ERROR_PLAYBACK_STOP_FAILEDTOREMOVECALLBACKS;
    }

    error = player_removeBPMCallbacks(player);
    if(error != SSP_OK) {
        return SSP_ERROR_UNKNOWN;
    }

    success = BASS_StreamFree(player->handles->fxChannel);
    if(!success) {
        return SSP_ERROR_PLAYBACK_STOP_FAILEDTOFREESTREAM;
    }

    error = playlist_disposeChannels(player->playlist);
    if(error != SSP_OK) {
        return SSP_ERROR_PLAYBACK_STOP_FAILEDTODISPOSECHANNELS;
    }

    player->playhead->positionAfterUnpause = 0;
    player->playhead->positionOffset = 0;
    player->playhead->isPlayingLoop = false;
    player_updateState(player, SSP_PLAYER_STATE_STOPPED);

    return SSP_OK;
}

SSP_ERROR player_play(SSP_PLAYER* player) {
    return player_playWithOptions(player, 0, 0, false);
}

SSP_ERROR player_playWithOptions(SSP_PLAYER* player, int startIndex, uint64_t startPosition, bool startPaused) {
    SSP_ERROR error;

    log_text("player_play\n");
    if(player->playhead->state == SSP_PLAYER_STATE_PLAYING) {
        if(player->playhead->isPlayingLoop) {
            player_stopLoop(player);
        }

        player_stop(player);
    }

    log_text("player_play - Getting current index and count...\n");
    int count = playlist_getCount(player->playlist);

    int channelsToLoad = count - startIndex;
    if(channelsToLoad > 2)
        channelsToLoad = 2;

    if(channelsToLoad == 0) {
        log_text("player_play - ERROR: There are no channels to play!\n");
        return SSP_ERROR_PLAYBACK_PLAY_NOCHANNELSTOPLAY;
    }

    SSP_PLAYLISTITEM* firstItem = playlist_getItemAt(player->playlist, startIndex);
    for(int a = startIndex; a < startIndex + channelsToLoad; a++) {
        log_textf("player_play - Loading playlist item %d...\n", a);
        SSP_PLAYLISTITEM* item = playlist_getItemAt(player->playlist, a);
        playlistitem_load(item, player->mixer->useFloatingPoint);
    }

    log_text("player_play - Setting stream channel and proc...\n");
    player->handles->streamProc = (STREAMPROC*)player_streamProc;

    player->handles->streamChannel = bass_createMemoryStream(firstItem->sampleRate, 2, player->mixer->useFloatingPoint, player->handles->streamProc, player);
    if(player->handles->streamChannel == 0) {
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEMEMORYSTREAM;
    }

    // FX channel is for pitch and time shifting
    player->handles->fxChannel = bass_createStreamForTimeShifting(player->handles->streamChannel, true, player->mixer->useFloatingPoint);
    if(player->handles->fxChannel == 0) {
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEFXCHANNEL;
    }

    player->handles->mixerChannel = bass_createMixerStream(player->mixer->sampleRate, 2, false, player->mixer->useFloatingPoint);
    if(player->handles->mixerChannel == 0) {
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEMIXERCHANNEL;
    }

    // Add FX channel to mixer
    bool success = BASS_Mixer_StreamAddChannel(player->handles->mixerChannel, player->handles->fxChannel, BASS_MIXER_BUFFER);
    if(!success) {
        bass_getError("BASS_Mixer_StreamAddChannel");
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOADDSTREAMTOMIXER;
    }

    error = player_addBPMCallbacks(player);
    if(error != SSP_OK) {
        return error;
    }

    player_setVolume(player, player->playhead->volume);

    error = player_createEQStage(player);
    if(error != SSP_OK) {
        return error;
    }

    //if(player->playhead->isEQEnabled) {
        error = player_applyEQ(player, player->eqPreset);
        if (error != SSP_OK) {
            return error;
        }
    //}

    if(player->playhead->repeatType == SSP_PLAYER_REPEAT_SONG) {
        int result = BASS_ChannelFlags(firstItem->channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
        if (result == -1) {
            bass_getError("BASS_ChannelFlags");
            return SSP_ERROR_UNKNOWN;
        }
    }

    SSP_PLAYLISTITEM* currentItem = playlist_getCurrentItem(player->playlist);
    error = player_setSyncCallback(player, currentItem->length);
    if(error != SSP_OK) {
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSETSYNCCALLBACK;
    }

    player->playlist->currentMixerIndex = startIndex;

    success = BASS_Start();
    if(!success) {
        bass_getError("BASS_Start");
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSTART;
    }

    success = BASS_ChannelPlay(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("BASS_ChannelPlay");
        return SSP_ERROR_PLAYBACK_PLAY_FAILEDTOPLAYCHANNEL;
    }

    if (startPaused) {
        if(startPosition > 0) {
            player_setPosition(player, startPosition);
        }

        success = BASS_Pause();
        if(!success) {
            bass_getError("BASS_Pause");
            return SSP_ERROR_UNKNOWN;
        }
    }

    player_updateState(player, startPaused ? SSP_PLAYER_STATE_PAUSED : SSP_PLAYER_STATE_PLAYING);

    if(player->playlist->callbackPlaylistIndexChanged != NULL) {
        player->playlist->callbackPlaylistIndexChanged(player->playlist->callbackPlaylistIndexChangedUser);
    }

    log_text("player_play - Finished playback sequence!\n");
    return SSP_OK;
}

SSP_ERROR player_previous(SSP_PLAYER* player) {
    SSP_ERROR error = player_stop(player);
    if(error != SSP_OK) {
        return error;
    }

    if(player->playlist->currentIndex > 0) {
        player->playlist->currentIndex--;
    }

    error = player_play(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}

SSP_ERROR player_next(SSP_PLAYER* player) {
    SSP_ERROR error = player_stop(player);
    if(error != SSP_OK) {
        return error;
    }

    if(player->playlist->currentIndex < playlist_getCount(player->playlist) - 1) {
        player->playlist->currentIndex++;
    }

    error = player_play(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}

SSP_ERROR player_goTo(SSP_PLAYER* player, int index) {
    SSP_ERROR error = player_stop(player);
    if(error != SSP_OK) {
        return error;
    }

    player->playlist->currentIndex = index;

    error = player_play(player);
    if(error != SSP_OK) {
        return error;
    }

    return SSP_OK;
}
