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

    uint64_t offset = 0 - (position / 2);
    if(!playbackStopped) {
//        // Multiply by 1.5 (I don't really know why, but this works for 48000Hz and 96000Hz. Maybe a bug in BASS with FLAC files?)
//        if (Playlist.CurrentItem.AudioFile.FileType == AudioFileFormat.FLAC && Playlist.Items[nextPlaylistIndex].AudioFile.SampleRate > 44100)
//            offset = (long)((float)offset * 1.5f);

        // Check if the sample rate needs to be changed (i.e. main channel sample rate different than the decoding file)
        float sampleRate;
        bool success = BASS_ChannelGetAttribute(player->handles->mixerChannel, BASS_ATTRIB_FREQ, &sampleRate);
        if(!success) {
            int bassError = BASS_ErrorGetCode();
            if(bassError != BASS_OK) {
                log_textf("player_playerSyncProc - Error getting channel attributes: %d", bassError);
                return;
            }
        }

        SSP_PLAYLISTITEM* nextItem = playlist_getItemAt(player->playlist, nextPlaylistIndex);
        if(nextItem != NULL && sampleRate != nextItem->sampleRate) {
            log_textf("player_playerSyncProc - Switching mixer sample rate to %d", nextItem->sampleRate);
            BASS_ChannelSetAttribute(player->handles->mixerChannel, BASS_ATTRIB_FREQ, nextItem->sampleRate);
        }

        player->playhead->positionOffset = offset;
    }

    success = BASS_ChannelLock(player->handles->mixerChannel, false);
    if(!success) {
        bass_getError("player_playerSyncProc");
        return;
    }

    //player_removeSyncCallbacks(<#(SSP_PLAYER*)player#>)
//    RemoveSyncCallback(handle);
    // We may not have to call this because of BASS_SYNC_ONETIME

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

//            if (IsEQEnabled)
//                RemoveEQ();

        playlist_disposeChannels(player->playlist);
        player_updateState(player, SSP_PLAYER_STATE_STOPPED);
    }

    if(player->playlist->callbackPlaylistIndexChanged != NULL) {
        log_text("player_playerSyncProc - Calling callbackPlaylistIndexChanged...\n");
        player->playlist->callbackPlaylistIndexChanged(player->playlist->callbackPlaylistIndexChangedUser);
    }

    log_text("player_playerSyncProc (END)\n");

//        // Create data
//        PlayerPlaylistIndexChangedData eventData = new PlayerPlaylistIndexChangedData();
//        eventData.IsPlaybackStopped = playbackStopped;
//        eventData.PlaylistName = "New playlist 1";
//        eventData.PlaylistCount = Playlist.Items.Count;
//        eventData.PlaylistIndex = Playlist.CurrentItemIndex;
//
//        // If the playback hasn't stopped, fill more event data
//        if (playbackStopped)
//        {
//            // Set event data
//            eventData.AudioFileStarted = null;
//            eventData.AudioFileEnded = Playlist.CurrentItem.AudioFile;
//        }
//        else
//        {
//            // Set event data
//            eventData.AudioFileStarted = Playlist.CurrentItem.AudioFile;
//            if (Playlist.CurrentItemIndex < Playlist.Items.Count - 2)
//                eventData.NextAudioFile = Playlist.Items[Playlist.CurrentItemIndex + 1].AudioFile;
//
//            // Is this the first item, and did the last song of the playlist just play?
//            if (Playlist.CurrentItemIndex == 0 && playlistBackToStart)
//            {
//                // The audio file that just finished was the last of the playlist
//                eventData.AudioFileEnded = Playlist.Items[Playlist.Items.Count - 1].AudioFile;
//            }
//                // Make sure this is not the first item
//            else if (Playlist.CurrentItemIndex > 0)
//            {
//                // The audio file that just finished was the last one
//                eventData.AudioFileEnded = Playlist.Items[Playlist.CurrentItemIndex - 1].AudioFile;
//            }
//        }
//
//        // Raise event
//        OnPlaylistIndexChanged(eventData);
}

SSP_ERROR player_setSyncCallback(SSP_PLAYER* player, uint64_t position) {
    log_textf("player_setSyncCallback - position: %"PRIu64"\n", position);
    HSYNC sync = BASS_Mixer_ChannelSetSync(player->handles->fxChannel, BASS_SYNC_POS, position, player_playerSyncProc, player);
    if(sync == 0) {
        return bass_getError("player_setSyncCallback");
    }

    // Add to list to remove later
    player->handles->syncProcCount++;
    player->handles->syncProcHandles[player->handles->syncProcCount-1] = sync;

    return SSP_OK;
}

SSP_ERROR player_removeSyncCallbacks(SSP_PLAYER* player) {
    // Remove sync procs
    for(int a = 0; a < player->handles->syncProcCount; a++) {
        bool success = BASS_Mixer_ChannelRemoveSync(player->handles->fxChannel, player->handles->syncProcHandles[a]);
        if(!success) {
            return bass_getError("player_removeSyncCallbacks");
        }
    }

    // Reset list
    player->handles->syncProcCount = 0;

    return SSP_OK;
}
