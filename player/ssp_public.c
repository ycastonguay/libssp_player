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
#include "ssp_bass.h"
#include "ssp_public.h"
#include "ssp_privatestructs.h"
#include "ssp_playlist.h"
#include "ssp_player.h"
#include "ssp_log.h"
#include "ssp_eqpreset.h"
#include "ssp_device.h"
#include "ssp_playlistitem.h"
#include "ssp_loop.h"
#include "ssp_mixer.h"
#include "ssp_structs.h"
#include "ssp_decoder.h"
#include "ssp_util.h"

static SSP_PLAYER* sspPlayer = NULL;

#pragma mark Initialization

int SSP_GetVersion() {
    return SSP_VERSION;
}

SSP_ERROR SSP_Init(const char* pathForPlugins) {
    if(sspPlayer == NULL) {
        sspPlayer = player_create();
    }

    sspPlayer->pathForPlugins = copystr((char *)sspPlayer->pathForPlugins, pathForPlugins);
    return player_init(sspPlayer);
}

SSP_ERROR SSP_InitDevice(int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint) {
    return player_initDevice(sspPlayer, deviceId, sampleRate, bufferSize, updatePeriod, useFloatingPoint);
}

SSP_ERROR SSP_FreeDevice() {
    return player_freeDevice(sspPlayer);
}

SSP_ERROR SSP_Free() {
    SSP_ERROR error = player_free(sspPlayer);
    if(error != SSP_OK) {
        return error;
    }
    
    free(sspPlayer);
    sspPlayer = NULL;
    return SSP_OK;
}

#pragma mark iOS

void player_ios_notifyProc(DWORD status) {
	bool ended = status == BASS_IOSNOTIFY_INTERRUPT_END;

	// This event doesn't have a user pointer, so we have to use the player as a singleton
    if(sspPlayer->callbackAudioInterrupted != NULL) {
        sspPlayer->callbackAudioInterrupted(sspPlayer->callbackAudioInterruptedUser, ended);
    }
}

SSP_ERROR SSP_IOS_ConfigureAirPlay(bool enable) {
    bool success = BASS_SetConfig(BASS_CONFIG_IOS_MIXAUDIO, enable ? 0 : 1);
    if(!success) {
    	bass_getError("BASS_SetConfig(BASS_CONFIG_IOS_MIXAUDIO)");
    	return SSP_ERROR_UNKNOWN;
    }

    return SSP_OK;
}

SSP_ERROR SSP_IOS_ConfigureAudioInterruptionNotification(bool enable) {
    bool success = BASS_SetConfigPtr(BASS_CONFIG_IOS_NOTIFY, enable ? player_ios_notifyProc : NULL);
    if(!success) {
        bass_getError("BASS_SetConfigPtr(BASS_CONFIG_IOS_NOTIFY)");
        return SSP_ERROR_UNKNOWN;
    }

    return SSP_OK;
}

#pragma mark Properties

ssp_player_state_t SSP_GetState() {
    if(sspPlayer == NULL || sspPlayer->playhead == NULL) {
        return SSP_PLAYER_STATE_UNINITIALIZED;
    }

    return sspPlayer->playhead->state;
}

void SSP_GetDevice(SSP_DEVICE* device) {
    device_copy(device, sspPlayer->device);
}

void SSP_GetMixer(SSP_MIXER* mixer) {
    mixer_copy(mixer, sspPlayer->mixer);
}

SSP_ERROR SSP_SetBufferSize(int bufferSize) {
    return player_setBufferSize(sspPlayer, bufferSize);
}

SSP_ERROR SSP_SetUpdatePeriod(int updatePeriod) {
    return player_setUpdatePeriod(sspPlayer, updatePeriod);
}

#pragma mark Callbacks

void SSP_SetLogCallback(player_log_cb cb, void* user) {
    log_setCallback(cb, user);
}

void SSP_RemoveLogCallback() {
    log_removeCallback();
}

void SSP_SetPlaylistIndexChangedCallback(player_playlistindexchanged_cb cb, void *user) {
    player_setPlaylistIndexChangedCallback(sspPlayer, cb, user);
}

void SSP_RemovePlaylistIndexChangedCallback() {
    player_removePlaylistIndexChangedCallback(sspPlayer);
}

void SSP_SetPlaylistEndedCallback(player_playlistended_cb cb, void* user) {
    player_setPlaylistEndedCallback(sspPlayer, cb, user);
}

void SSP_RemovePlaylistEndedCallback() {
    player_removePlaylistEndedCallback(sspPlayer);
}

void SSP_SetStateChangedCallback(player_statechanged_cb cb, void* user) {
    player_setStateChangedCallback(sspPlayer, cb, user);
}

void SSP_RemoveStateChangedCallback() {
    player_removeStateChangedCallback(sspPlayer);
}

void SSP_SetLoopPlaybackStartedCallback(player_loopplaybackstarted_cb cb, void* user) {
    player_setLoopPlaybackStartedCallback(sspPlayer, cb, user);
}

void SSP_RemoveLoopPlaybackStartedCallback() {
    player_removeLoopPlaybackStartedCallback(sspPlayer);
}

void SSP_SetLoopPlaybackStoppedCallback(player_loopplaybackstopped_cb cb, void* user) {
    player_setLoopPlaybackStoppedCallback(sspPlayer, cb, user);
}

void SSP_RemoveLoopPlaybackStoppedCallback() {
    player_removeLoopPlaybackStoppedCallback(sspPlayer);
}

void SSP_SetAudioInterruptedCallback(player_audiointerrupted_cb cb, void* user) {
    player_setAudioInterruptedCallback(sspPlayer, cb, user);
}

void SSP_RemoveAudioInterruptedCallback() {
    player_removeAudioInterruptedCallback(sspPlayer);
}

void SSP_SetBPMDetectedCallback(player_bpmdetected_cb cb, void* user) {
    player_setBPMDetectedCallback(sspPlayer, cb, user);
}

void SSP_RemoveBPMDetectedCallback() {
    player_removeBPMDetectedCallback(sspPlayer);
}

#pragma mark Playback

SSP_ERROR SSP_Play() {
    return player_play(sspPlayer);
}

SSP_ERROR SSP_PlayWithOptions(int startIndex, uint64_t startPosition, bool startPaused) {
    return player_playWithOptions(sspPlayer, startIndex, startPosition, startPaused);
}

SSP_ERROR SSP_Pause() {
    return player_pause(sspPlayer);
}

SSP_ERROR SSP_Stop() {
    return player_stop(sspPlayer);
}

SSP_ERROR SSP_Previous() {
    return player_previous(sspPlayer);
}

SSP_ERROR SSP_Next() {
    return player_next(sspPlayer);
}

SSP_ERROR SSP_GoTo(int index) {
    return player_goTo(sspPlayer, index);
}

#pragma mark Playlist

SSP_ERROR SSP_Playlist_AddItem(char* filePath, char* audioFileId) {
    return playlist_addItem(sspPlayer->playlist, filePath, audioFileId);
}

SSP_ERROR SSP_Playlist_InsertItemAt(char* filePath, char* audioFileId, int index) {
    return playlist_insertItemAt(sspPlayer->playlist, filePath, audioFileId, index);
}

SSP_ERROR SSP_Playlist_RemoveItemAt(int index) {
    return playlist_removeItemAt(sspPlayer->playlist, index);
}

SSP_ERROR SSP_Playlist_Clear() {
    return playlist_clear(sspPlayer->playlist);
}

void SSP_Playlist_GetItemAt(int index, SSP_PLAYLISTITEM* item) {
    SSP_PLAYLISTITEM* localItem = playlist_getItemAt(sspPlayer->playlist, index);
    if(localItem != NULL) {
        playlistitem_copy(localItem, item);
    }
}

void SSP_Playlist_GetItemFromId(int id, SSP_PLAYLISTITEM* item) {
	SSP_PLAYLISTITEM* localItem = playlist_getItemFromId(sspPlayer->playlist, id);
	if (localItem != NULL) {
		playlistitem_copy(localItem, item);
	}
}

int SSP_Playlist_GetIndexFromId(int id) {
	return playlist_getIndexFromId(sspPlayer->playlist, id);
}

int SSP_Playlist_GetCount() {
    return playlist_getCount(sspPlayer->playlist);
}

int SSP_Playlist_GetCurrentIndex() {
    return sspPlayer->playlist->currentIndex;
}

#pragma mark EQ Presets

void SSP_GetEQPreset(SSP_EQPRESET* preset) {
    eqpreset_copy(preset, sspPlayer->eqPreset);
}

SSP_ERROR SSP_SetEQPreset(SSP_EQPRESET* preset) {
    return player_applyEQ(sspPlayer, preset, true);
}

SSP_ERROR SSP_SetEQPresetBand(int band, float gain) {
    return player_updateEQBand(sspPlayer, band, gain);
}

SSP_ERROR SSP_ResetEQPreset(SSP_EQPRESET* preset) {
    eqpreset_reset(preset);
    return SSP_OK;
}

bool SSP_GetEQEnabled() {
    return sspPlayer->playhead->isEQEnabled;
}

SSP_ERROR SSP_SetEQEnabled(bool enabled) {
    return player_enableEQ(sspPlayer, enabled);
}

SSP_ERROR SSP_ResetEQ() {
    return player_resetEQ(sspPlayer);
}

SSP_ERROR SSP_NormalizeEQ() {
    return player_normalizeEQ(sspPlayer);
}

#pragma mark Seek / Position

SSP_ERROR SSP_GetPosition(SSP_POSITION* position) {
    return player_getPositionStruct(sspPlayer, position);
}

SSP_ERROR SSP_SetPosition(uint64_t position) {
    log_textf("SSP_SetPosition - position: %"PRIu64"\n", position);
    return player_setPosition(sspPlayer, position);
}

SSP_ERROR SSP_SetPositionPercentage(float position) {
    log_textf("SSP_SetPositionPercentage - position: %f\n", position);
    return player_setPositionPercentage(sspPlayer, position);
}

SSP_ERROR SSP_GetPositionFromBytes(uint64_t bytes, SSP_POSITION* position) {
    return player_getPositionFromBytes(sspPlayer, bytes, position);
}

SSP_ERROR SSP_GetPositionFromPercentage(float percentage, SSP_POSITION* position) {
    return player_getPositionFromPercentage(sspPlayer, percentage, position);
}

#pragma mark Playhead

bool SSP_GetIsShuffle() {
    return player_getIsShuffle(sspPlayer);
}

SSP_ERROR SSP_SetIsShuffle(bool shuffle) {
    return player_setIsShuffle(sspPlayer, shuffle);
}

ssp_player_repeat_t SSP_GetRepeatType() {
    return player_getRepeatType(sspPlayer);
}

SSP_ERROR SSP_SetRepeatType(ssp_player_repeat_t repeat) {
    return player_setRepeatType(sspPlayer, repeat);
}

SSP_ERROR SSP_ToggleRepeatType() {
    ssp_player_repeat_t repeat = player_getRepeatType(sspPlayer);
    switch(repeat) {
        case SSP_PLAYER_REPEAT_OFF:
            return player_setRepeatType(sspPlayer, SSP_PLAYER_REPEAT_PLAYLIST);
        case SSP_PLAYER_REPEAT_PLAYLIST:
            return player_setRepeatType(sspPlayer, SSP_PLAYER_REPEAT_SONG);
        case SSP_PLAYER_REPEAT_SONG:
            return player_setRepeatType(sspPlayer, SSP_PLAYER_REPEAT_OFF);
        default:
            break;
    }

    return SSP_OK;
}

float SSP_GetVolume() {
    return player_getVolume(sspPlayer);
}

SSP_ERROR SSP_SetVolume(float volume) {
    return player_setVolume(sspPlayer, volume);
}

float SSP_GetTimeShifting() {
    return player_getTimeShifting(sspPlayer);
}

SSP_ERROR SSP_SetTimeShifting(float timeShifting) {
    return player_setTimeShifting(sspPlayer, timeShifting);
}

int SSP_GetPitchShifting() {
    return player_getPitchShifting(sspPlayer);
}

SSP_ERROR SSP_SetPitchShifting(int pitchShifting) {
    return player_setPitchShifting(sspPlayer, pitchShifting);
}

bool SSP_GetIsSettingPosition() {
    return sspPlayer->playhead->isSettingPosition;
}

bool SSP_GetIsPlayingLoop() {
    return sspPlayer->playhead->isPlayingLoop;
}

#pragma mark Data

int SSP_GetMixerData(void* buffer, int length) {
    return player_getMixerData(sspPlayer, buffer, length);
}

uint64_t SSP_GetBytesFromSecondsForCurrentChannel(float seconds) {
    return player_getBytesFromSecondsForCurrentChannel(sspPlayer, seconds);
}

uint64_t SSP_GetDataAvailable() {
    return player_getDataAvailable(sspPlayer);
}

#pragma mark Encoder

SSP_ERROR SSP_StartEncode(ssp_player_encoder_t encoder) {
    return player_startEncode(sspPlayer, encoder);
}

SSP_ERROR SSP_StopEncode() {
    return player_stopEncode(sspPlayer);
}

SSP_ERROR SSP_StartCast(SSP_CAST_SERVER* server) {
    return player_startCast(sspPlayer, server);
}

SSP_ERROR SSP_StopCast() {
    return player_stopCast(sspPlayer);
}

#pragma mark Loops

SSP_ERROR SSP_StartLoop(SSP_LOOP* loop) {
    return player_startLoop(sspPlayer, loop);
}

SSP_ERROR SSP_UpdateLoop(SSP_LOOP* loop) {
    return player_updateLoop(sspPlayer, loop);
}

SSP_ERROR SSP_StopLoop() {
    return player_stopLoop(sspPlayer);
}

void SSP_GetLoop(SSP_LOOP* loop) {
    loop_copy(loop, sspPlayer->loop);
}

#pragma mark Decoder

uint32_t SSP_Decoder_CreateStream(char* filePath, bool useFloatingPoint) {
    return decoder_createStream(filePath, useFloatingPoint);
}

SSP_ERROR SSP_Decoder_FreeStream(uint32_t handle) {
    return decoder_freeStream(handle);
}

uint64_t SSP_Decoder_GetLength(uint32_t handle) {
    return decoder_getLength(handle);
}

uint64_t SSP_Decoder_GetData(uint32_t handle, void* buffer, int length) {
    return decoder_getData(handle, buffer, length);
}

#pragma mark Device Detection

int SSP_GetOutputDeviceCount() {
    return device_getOutputDeviceCount();
}

bool SSP_GetOutputDevice(int index, SSP_DEVICE *device) {
    return device_getOutputDevice(index, device);
}
