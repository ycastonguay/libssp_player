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
#include <inttypes.h>
#include "../bass/bassmix.h"
#include "ssp_player.h"
#include "ssp_playlist.h"
#include "ssp_bass.h"
#include "ssp_log.h"
#include "ssp_playlistitem.h"
#include "vector.h"

SSP_ERROR player_setSyncCallbackAfterChangingPlaylistItem(SSP_PLAYER *player) {
    log_text("player_setSyncCallbackAfterChangingPlaylistItem\n");

    bool success = BASS_ChannelLock(player->handles->mixerChannel, true);
    if(!success) {
        return bass_getError("player_setSyncCallbackAfterChangingPlaylistItem");
    }

    uint64_t position = BASS_ChannelGetPosition(player->handles->fxChannel, BASS_POS_BYTE);
    if(position == -1) {
        return bass_getError("player_setSyncCallbackAfterChangingPlaylistItem");
    }

    DWORD buffered = BASS_ChannelGetData(player->handles->mixerChannel, 0, BASS_DATA_AVAILABLE);
    if(buffered == -1) {
        return bass_getError("player_setSyncCallbackAfterChangingPlaylistItem");
    }

    // Calculate the new sync position
    SSP_PLAYLISTITEM *item = playlist_getCurrentMixerItem(player->playlist);
    uint64_t audioLength = item->length;
    uint64_t syncPos = position + buffered + audioLength;
    player_setSyncCallback(player, syncPos);

    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        return bass_getError("player_setSyncCallbackAfterChangingPlaylistItem");
    }

    return SSP_OK;
}

void player_tryToLoadNextPlaylistItem(SSP_PLAYER* player) {
    int nextMixPlaylistIndex = player->playlist->currentMixerIndex + 1;
    log_textf("player_tryToLoadNextPlaylistItem - nextMixPlaylistIndex: %d\n", nextMixPlaylistIndex);

    if(player->playlist->currentMixerIndex < playlist_getCount(player->playlist) - 1) {
        log_text("player_tryToLoadNextPlaylistItem - Loading next playlist item...\n");
        SSP_PLAYLISTITEM *item = playlist_getItemAt(player->playlist, nextMixPlaylistIndex);
        playlistitem_load(item, player->mixer->useFloatingPoint);
    }
}

bool player_skipToNextPlaylistItemAndDetermineIfPlaybackMustContinue(SSP_PLAYER* player) {
    player->loop = NULL;

    log_text("player_skipToNextPlaylistItemAndDetermineIfPlaybackMustContinue\n");
    // lock (_lockerplaylist) -- is this necessary?

    if(player->playlist->currentIndex == playlist_getCount(player->playlist) - 1) {
        if(player->playhead->repeatType == SSP_PLAYER_REPEAT_PLAYLIST) {
            player->playlist->currentMixerIndex = 0;
            //player->playlist->currentIndex = 0;

            // Load the first item of the playlist
            SSP_PLAYLISTITEM *item = playlist_getCurrentMixerItem(player->playlist);
            playlistitem_load(item, player->mixer->useFloatingPoint);

            // Load the second item of the playlist (TODO: is it possible to do this asynchronously?)
            player_tryToLoadNextPlaylistItem(player);

            // Continue playing
            return true;
        }

        // End of playlist; stop playback
        return false;
    }

    // Load next playlist item
    player->playlist->currentMixerIndex++;
    player_tryToLoadNextPlaylistItem(player);
    player_setSyncCallbackAfterChangingPlaylistItem(player);

    // Continue playing
    return true;
}

DWORD CALLBACK player_streamProc(HSTREAM handle, float *buffer, DWORD length, void *user) {
    DWORD data = -1;
    SSP_PLAYER *player = (SSP_PLAYER*)user;
    SSP_PLAYLISTITEM *currentItem = playlist_getCurrentMixerItem(player->playlist);

    int active = BASS_ChannelIsActive(currentItem->channel);
    if(active == BASS_ACTIVE_PLAYING) {
        data = BASS_ChannelGetData(currentItem->channel, buffer, length);
        if(data == -1) {
            bass_getError("player_streamProc");
            return BASS_STREAMPROC_END;
        }

        //printf("player_streamProc - BASS_ACTIVE_PLAYING - length: %d - data: %d\n", length, data);
        return data;
    }
    else if(active == BASS_ACTIVE_STOPPED) {
        // Skip to next song
        bool continuePlaying = player_skipToNextPlaylistItemAndDetermineIfPlaybackMustContinue(player);
        if (continuePlaying)
        {
            // The current item has changed, update it
            currentItem = playlist_getCurrentMixerItem(player->playlist);
            data = BASS_ChannelGetData(currentItem->channel, buffer, length);
            if(data == -1) {
                bass_getError("player_streamProc");
                return BASS_STREAMPROC_END;
            }

            //printf("player_streamProc - BASS_ACTIVE_STOPPED - length: %d - data: %d\n", length, data);
            return data;
        }
    }

    log_text("player_streamProc - BASS_STREAMPROC_END");
    return BASS_STREAMPROC_END;
}

void CALLBACK player_playerSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    log_text("player_playerSyncProc\n");
    SSP_PLAYER *player = (SSP_PLAYER*)user;

    bool playbackStopped = false;
    bool playlistBackToStart = false;
    int nextPlaylistIndex = 0;

    bool success = BASS_ChannelLock(player->handles->mixerChannel, true);
    if(!success) {
        // TODO: how do we manage an error inside a callback?
        bass_getError("player_playerSyncProc");
        return;
    }

    uint64_t position = BASS_ChannelGetPosition(player->handles->fxChannel, BASS_POS_BYTE);
    if(position == -1) {
        bass_getError("player_playerSyncProc");
        return;
    }

    DWORD buffered = BASS_ChannelGetData(player->handles->mixerChannel, 0, BASS_DATA_AVAILABLE);
    if(buffered == -1) {
        bass_getError("player_playerSyncProc");
        return;
    }

    // Is this the last song?
    if(player->playlist->currentIndex == playlist_getCount(player->playlist) - 1) {
        if(player->playhead->repeatType == SSP_PLAYER_REPEAT_PLAYLIST) {
            nextPlaylistIndex = 0;
            playlistBackToStart = true;
        }
        else {
            playbackStopped = true;
        }
    }
    else
    {
        nextPlaylistIndex = player->playlist->currentIndex + 1;
    }

    log_textf("player_playerSyncProc - playbackStopped: %d playlistBackToStart: %d nextPlaylistIndex: %d\n", playbackStopped, playlistBackToStart, nextPlaylistIndex);

    uint64_t offset = 0 - position + buffered;
    if(!playbackStopped) {
//        if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.Items[nextPlaylistIndex].AudioFile.SampleRate > 44100)
//            offset = (long)((float)offset * 1.5f);

        // Check if the sample rate needs to be changed (i.e. main channel sample rate different than the decoding file)
        float sampleRate;
        bool success = BASS_ChannelGetAttribute(player->handles->streamChannel, BASS_ATTRIB_FREQ, &sampleRate);
        if(!success) {
            int bassError = BASS_ErrorGetCode();
            if(bassError != BASS_OK) {
                log_textf("player_playerSyncProc - Error getting channel attributes: %d", bassError);
                return;
            }
        }

        SSP_PLAYLISTITEM* nextItem = playlist_getItemAt(player->playlist, nextPlaylistIndex);
        if(nextItem != NULL) {
	        float newSampleRate = nextItem->sampleRate;
	        log_textf("player_playerSyncProc - Mixer sample rate is %f; Next playlist item sample rate is %f", sampleRate, newSampleRate);
	        if(sampleRate != newSampleRate) {
	        	log_textf("player_playerSyncProc - Switching sample rate to %f", newSampleRate);
	            BASS_ChannelSetAttribute(player->handles->streamChannel, BASS_ATTRIB_FREQ, newSampleRate);
	        }
        }

        player->playhead->positionOffset = offset;
    }

    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("player_playerSyncProc");
        return;
    }

    SSP_ERROR error = player_removeSyncCallback(player, handle);
    if(error != SSP_OK) {
        return;
    }

    // Is this the last song?
    if(player->playlist->currentIndex == playlist_getCount(player->playlist) - 1) {
        if(player->playhead->repeatType == SSP_PLAYER_REPEAT_PLAYLIST) {
            player->playlist->currentIndex = 0;
        }
    }
    else {
        player->playlist->currentIndex++;
    }

    if(playbackStopped) {
        player_stop(player);
    }

    if(player->playlist->callbackPlaylistIndexChanged != NULL) {
        player->playlist->callbackPlaylistIndexChanged(player->playlist->callbackPlaylistIndexChangedUser);
    }
}

SSP_ERROR player_setSyncCallback(SSP_PLAYER* player, uint64_t position) {
    log_textf("player_setSyncCallback - position: %"PRIu64"\n", position);

    HSYNC sync = BASS_Mixer_ChannelSetSync(player->handles->fxChannel, BASS_SYNC_POS, position, player_playerSyncProc, player);
    if(sync == 0) {
        bass_getError("player_setSyncCallback");
        return SSP_ERROR_UNKNOWN;
    }

    // Allocate some memory for the value on the heap (TODO: check if this is the right thing to do)
    HSYNC*syncHeap = malloc(sizeof(HSYNC));
    *syncHeap = sync;
    vector_add(player->handles->syncProcHandles, syncHeap);

    return SSP_OK;
}

SSP_ERROR player_removeSyncCallbacks(SSP_PLAYER* player) {
    for(int a = 0; a < vector_total(player->handles->syncProcHandles); a++) {
        HSYNC* handle = (HSYNC*)vector_get(player->handles->syncProcHandles, a);
        bool success = BASS_Mixer_ChannelRemoveSync(player->handles->fxChannel, *handle);
        if(!success) {
            return bass_getError("player_removeSyncCallbacks");
        }

        // Don't forget to free the item from the heap
        free(handle);
    }

    // Empty vector
    vector_free(player->handles->syncProcHandles);
    free(player->handles->syncProcHandles);
    player->handles->syncProcHandles = NULL;

    // Initialize vector
    player->handles->syncProcHandles = malloc(sizeof(vector));
    vector_init(player->handles->syncProcHandles);

    return SSP_OK;
}

SSP_ERROR player_removeSyncCallback(SSP_PLAYER* player, uint32_t handle) {
    bool success = BASS_Mixer_ChannelRemoveSync(player->handles->fxChannel, handle);
    if(!success) {
        return bass_getError("player_removeSyncCallback");
    }

    int index = -1;
    HSYNC* currentHandle = NULL;
    for(int a = 0; a < vector_total(player->handles->syncProcHandles); a++) {
        currentHandle = (HSYNC*)vector_get(player->handles->syncProcHandles, a);
        if(*currentHandle == handle) {
            index = a;
            break;
        }
    }

    if(index >= 0) {
        vector_delete(player->handles->syncProcHandles, index);

        // Don't forget to free the item from the heap
        free(currentHandle);
    }

    return SSP_OK;
}
