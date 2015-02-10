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

#define SSP_VERSION 16

#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#else
#    define LIBRARY_API
#endif

LIBRARY_API int SSP_GetVersion();
LIBRARY_API SSP_ERROR SSP_Init(const char* pathForPlugins);
LIBRARY_API SSP_ERROR SSP_InitDevice(int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
LIBRARY_API SSP_ERROR SSP_FreeDevice();
LIBRARY_API SSP_ERROR SSP_Free();
LIBRARY_API ssp_player_state_t SSP_GetState();

// Properties
LIBRARY_API void SSP_GetDevice(SSP_DEVICE* device);
LIBRARY_API void SSP_GetMixer(SSP_MIXER* mixer);

// EQ
LIBRARY_API void SSP_GetEQPreset(SSP_EQPRESET* preset);
LIBRARY_API SSP_ERROR SSP_SetEQPreset(SSP_EQPRESET* preset);
LIBRARY_API SSP_ERROR SSP_SetEQPresetBand(int band, float gain);

LIBRARY_API bool SSP_GetEQEnabled();
LIBRARY_API SSP_ERROR SSP_SetEQEnabled(bool enabled);

LIBRARY_API SSP_ERROR SSP_ResetEQ();
LIBRARY_API SSP_ERROR SSP_NormalizeEQ();

// Loops
LIBRARY_API SSP_ERROR SSP_StartLoop(SSP_LOOP* loop);
LIBRARY_API SSP_ERROR SSP_UpdateLoop(SSP_LOOP* loop);
LIBRARY_API SSP_ERROR SSP_StopLoop();

// Playback
LIBRARY_API SSP_ERROR SSP_Play();
LIBRARY_API SSP_ERROR SSP_Pause();
LIBRARY_API SSP_ERROR SSP_Stop();
LIBRARY_API SSP_ERROR SSP_Previous();
LIBRARY_API SSP_ERROR SSP_Next();
LIBRARY_API SSP_ERROR SSP_GoTo(int index);
//void SSP_GoTo(int playlistItemId); // how do we manage ids?

// Playhead
LIBRARY_API bool SSP_GetIsShuffle();
LIBRARY_API SSP_ERROR SSP_SetIsShuffle(bool shuffle);

LIBRARY_API ssp_player_repeat_t SSP_GetRepeatType();
LIBRARY_API SSP_ERROR SSP_SetRepeatType(ssp_player_repeat_t repeat);

LIBRARY_API float SSP_GetVolume();
LIBRARY_API SSP_ERROR SSP_SetVolume(float volume);

LIBRARY_API float SSP_GetTimeShifting();
LIBRARY_API SSP_ERROR SSP_SetTimeShifting(float timeShifting);

LIBRARY_API int SSP_GetPitchShifting();
LIBRARY_API SSP_ERROR SSP_SetPitchShifting(int pitchShifting);

// Position
LIBRARY_API uint64_t SSP_GetPosition();
LIBRARY_API void SSP_GetPositionNew(SSP_POSITION* position);
LIBRARY_API SSP_ERROR SSP_SetPosition(uint64_t position);
//void SSP_SetPosition(double positionPercentage);

// Data
LIBRARY_API int SSP_GetMixerData(void* buffer, int length);

// Encoder
LIBRARY_API SSP_ERROR SSP_StartEncode(ssp_player_encoder_t encoder);
LIBRARY_API SSP_ERROR SSP_StopEncode();
LIBRARY_API SSP_ERROR SSP_StartCast(SSP_CAST_SERVER* server);
LIBRARY_API SSP_ERROR SSP_StopCast();

// Playlist
LIBRARY_API SSP_ERROR SSP_Playlist_AddItem(char* filePath);
LIBRARY_API SSP_ERROR SSP_Playlist_InsertItemAt(char* filePath, int index);
LIBRARY_API SSP_ERROR SSP_Playlist_RemoveItemAt(int index);
LIBRARY_API SSP_ERROR SSP_Playlist_Clear();
LIBRARY_API SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index);
LIBRARY_API void SSP_Playlist_GetItemAtNew(int index, SSP_PLAYLISTITEM* item);
LIBRARY_API int SSP_Playlist_GetCount();
LIBRARY_API int SSP_Playlist_GetCurrentIndex();

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

#endif /* defined(__player__ssp_public__) */
