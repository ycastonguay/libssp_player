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

#ifndef __player__ssp_public__
#define __player__ssp_public__

#include <stdio.h>
#include <stdbool.h>
#include "ssp_structs.h"
#include "ssp_errors.h"

#define SSP_VERSION 23

#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#else
#    define LIBRARY_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Initialization
LIBRARY_API int SSP_GetVersion();
LIBRARY_API SSP_ERROR SSP_Init(const char* pathForPlugins);
LIBRARY_API SSP_ERROR SSP_InitDevice(int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
LIBRARY_API SSP_ERROR SSP_FreeDevice();
LIBRARY_API SSP_ERROR SSP_Free();

// iOS-only
LIBRARY_API SSP_ERROR SSP_IOS_ConfigureAirPlay(bool enable);
LIBRARY_API SSP_ERROR SSP_IOS_ConfigureAudioInterruptionNotification(bool enable);

// Properties
LIBRARY_API ssp_player_state_t SSP_GetState();
LIBRARY_API void SSP_GetDevice(SSP_DEVICE* device);

// Mixer
LIBRARY_API void SSP_GetMixer(SSP_MIXER* mixer);
LIBRARY_API SSP_ERROR SSP_SetBufferSize(int bufferSize);
LIBRARY_API SSP_ERROR SSP_SetUpdatePeriod(int updatePeriod);

// EQ
LIBRARY_API void SSP_GetEQPreset(SSP_EQPRESET* preset);
LIBRARY_API SSP_ERROR SSP_SetEQPreset(SSP_EQPRESET* preset);
LIBRARY_API SSP_ERROR SSP_SetEQPresetBand(int band, float gain);
LIBRARY_API SSP_ERROR SSP_ResetEQPreset(SSP_EQPRESET* preset);

LIBRARY_API bool SSP_GetEQEnabled();
LIBRARY_API SSP_ERROR SSP_SetEQEnabled(bool enabled);

LIBRARY_API SSP_ERROR SSP_ResetEQ();
LIBRARY_API SSP_ERROR SSP_NormalizeEQ();

// Loops
LIBRARY_API SSP_ERROR SSP_StartLoop(SSP_LOOP* loop);
LIBRARY_API SSP_ERROR SSP_UpdateLoop(SSP_LOOP* loop);
LIBRARY_API SSP_ERROR SSP_StopLoop();
LIBRARY_API void SSP_GetLoop(SSP_LOOP* loop);

// Playback
LIBRARY_API SSP_ERROR SSP_Play();
LIBRARY_API SSP_ERROR SSP_PlayWithOptions(int startIndex, uint64_t startPosition, bool startPaused);
LIBRARY_API SSP_ERROR SSP_Pause();
LIBRARY_API SSP_ERROR SSP_Stop();
LIBRARY_API SSP_ERROR SSP_Previous();
LIBRARY_API SSP_ERROR SSP_Next();
LIBRARY_API SSP_ERROR SSP_GoTo(int index);
//LIBRARY_API SSP_ERROR SSP_GoToPlaylistItemId(int id);

// Playhead
LIBRARY_API bool SSP_GetIsShuffle();
LIBRARY_API SSP_ERROR SSP_SetIsShuffle(bool shuffle);

LIBRARY_API ssp_player_repeat_t SSP_GetRepeatType();
LIBRARY_API SSP_ERROR SSP_SetRepeatType(ssp_player_repeat_t repeat);
LIBRARY_API SSP_ERROR SSP_ToggleRepeatType();

LIBRARY_API float SSP_GetVolume();
LIBRARY_API SSP_ERROR SSP_SetVolume(float volume);

LIBRARY_API float SSP_GetTimeShifting();
LIBRARY_API SSP_ERROR SSP_SetTimeShifting(float timeShifting);

LIBRARY_API int SSP_GetPitchShifting();
LIBRARY_API SSP_ERROR SSP_SetPitchShifting(int pitchShifting);

LIBRARY_API bool SSP_GetIsSettingPosition();
LIBRARY_API bool SSP_GetIsPlayingLoop();

// Position
LIBRARY_API SSP_ERROR SSP_GetPosition(SSP_POSITION* position);
LIBRARY_API SSP_ERROR SSP_SetPosition(uint64_t position);
LIBRARY_API SSP_ERROR SSP_SetPositionPercentage(float position);
LIBRARY_API SSP_ERROR SSP_GetPositionFromBytes(uint64_t bytes, SSP_POSITION* position);
LIBRARY_API SSP_ERROR SSP_GetPositionFromPercentage(float percentage, SSP_POSITION* position);

// Data
LIBRARY_API int SSP_GetMixerData(void* buffer, int length);
LIBRARY_API uint64_t SSP_GetBytesFromSecondsForCurrentChannel(float seconds);
LIBRARY_API uint64_t SSP_GetDataAvailable();

// Encoder
LIBRARY_API SSP_ERROR SSP_StartEncode(ssp_player_encoder_t encoder);
LIBRARY_API SSP_ERROR SSP_StopEncode();
LIBRARY_API SSP_ERROR SSP_StartCast(SSP_CAST_SERVER* server);
LIBRARY_API SSP_ERROR SSP_StopCast();

// Playlist
LIBRARY_API SSP_ERROR SSP_Playlist_AddItem(char* filePath, char* audioFileId);
LIBRARY_API SSP_ERROR SSP_Playlist_InsertItemAt(char* filePath, char* audioFileId, int index);
LIBRARY_API SSP_ERROR SSP_Playlist_RemoveItemAt(int index);
LIBRARY_API SSP_ERROR SSP_Playlist_Clear();
LIBRARY_API void SSP_Playlist_GetItemAt(int index, SSP_PLAYLISTITEM* item);
LIBRARY_API void SSP_Playlist_GetItemFromId(int id, SSP_PLAYLISTITEM* item);
LIBRARY_API int SSP_Playlist_GetIndexFromId(int id);
LIBRARY_API int SSP_Playlist_GetCount();
LIBRARY_API int SSP_Playlist_GetCurrentIndex();

// Decoder (useful for peak file generation)
LIBRARY_API uint32_t SSP_Decoder_CreateStream(char* filePath, bool useFloatingPoint);
LIBRARY_API SSP_ERROR SSP_Decoder_FreeStream(uint32_t handle);
LIBRARY_API uint64_t SSP_Decoder_GetLength(uint32_t handle);
LIBRARY_API uint64_t SSP_Decoder_GetData(uint32_t handle, void* buffer, int length);

// Device detection
LIBRARY_API int SSP_GetOutputDeviceCount();
LIBRARY_API bool SSP_GetOutputDevice(int index, SSP_DEVICE *device);

// Callbacks
LIBRARY_API void SSP_SetPlaylistIndexChangedCallback(player_playlistindexchanged_cb cb, void* user);
LIBRARY_API void SSP_RemovePlaylistIndexChangedCallback();

LIBRARY_API void SSP_SetPlaylistEndedCallback(player_playlistended_cb cb, void* user);
LIBRARY_API void SSP_RemovePlaylistEndedCallback();

LIBRARY_API void SSP_SetStateChangedCallback(player_statechanged_cb cb, void* user);
LIBRARY_API void SSP_RemoveStateChangedCallback();

LIBRARY_API void SSP_SetLogCallback(player_log_cb cb, void* user);
LIBRARY_API void SSP_RemoveLogCallback();

LIBRARY_API void SSP_SetLoopPlaybackStartedCallback(player_loopplaybackstarted_cb cb, void* user);
LIBRARY_API void SSP_RemoveLoopPlaybackStartedCallback();

LIBRARY_API void SSP_SetLoopPlaybackStoppedCallback(player_loopplaybackstopped_cb cb, void* user);
LIBRARY_API void SSP_RemoveLoopPlaybackStoppedallback();

LIBRARY_API void SSP_SetAudioInterruptedCallback(player_audiointerrupted_cb cb, void* user);
LIBRARY_API void SSP_RemoveAudioInterruptedCallback();

LIBRARY_API void SSP_SetBPMDetectedCallback(player_bpmdetected_cb cb, void* user);
LIBRARY_API void SSP_RemoveBPMDetectedCallback();

#ifdef __cplusplus
}
#endif

#endif /* defined(__player__ssp_public__) */
