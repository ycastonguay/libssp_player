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

#define SSP_VERSION 14

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
LIBRARY_API SSP_ERROR SSP_Init();
LIBRARY_API SSP_ERROR SSP_InitDevice(int deviceId, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
LIBRARY_API SSP_ERROR SSP_FreeDevice();
LIBRARY_API SSP_ERROR SSP_Free();

// Callbacks
LIBRARY_API void SSP_SetPlaylistIndexChangedCallback(player_playlistindexchanged_cb cb, void* user);
LIBRARY_API void SSP_RemovePlaylistIndexChangedCallback();

LIBRARY_API void SSP_SetLogCallback(player_log_cb cb, void* user);
LIBRARY_API void SSP_RemoveLogCallback();

// Properties
LIBRARY_API void SSP_GetDevice(SSP_DEVICE* device);
LIBRARY_API SSP_PLAYHEAD* SSP_GetPlayhead();
LIBRARY_API SSP_MIXER* SSP_GetMixer();

// EQ
LIBRARY_API SSP_EQPRESET* SSP_GetEQPreset();
LIBRARY_API void SSP_SetEQPreset(SSP_EQPRESET* preset);

LIBRARY_API bool SSP_GetEQBypassed();
LIBRARY_API void SSP_SetEQBypassed(bool bypassed);

// Loops
LIBRARY_API SSP_LOOP* SSP_GetLoop();
LIBRARY_API void SSP_SetLoop(SSP_LOOP* loop);

// Playback
LIBRARY_API SSP_ERROR SSP_Play();
LIBRARY_API SSP_ERROR SSP_Pause();
LIBRARY_API SSP_ERROR SSP_Stop();
LIBRARY_API SSP_ERROR SSP_Previous();
LIBRARY_API SSP_ERROR SSP_Next();
LIBRARY_API SSP_ERROR SSP_GoTo(int index);
//void SSP_GoTo(int playlistItemId); // how do we manage ids?

LIBRARY_API void SSP_Seek();
LIBRARY_API uint64_t SSP_GetPosition();
LIBRARY_API SSP_ERROR SSP_SetPosition(uint64_t position);
//void SSP_SetPosition(double positionPercentage);

// Playlist
LIBRARY_API int SSP_Playlist_AddItem(char* filePath);
LIBRARY_API int SSP_Playlist_InsertItemAt(char* filePath, int index);
LIBRARY_API int SSP_Playlist_RemoveItemAt(int index);
LIBRARY_API int SSP_Playlist_Clear();
LIBRARY_API SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index);
LIBRARY_API int SSP_Playlist_GetCount();
LIBRARY_API int SSP_Playlist_GetCurrentIndex();

#endif /* defined(__player__ssp_public__) */
