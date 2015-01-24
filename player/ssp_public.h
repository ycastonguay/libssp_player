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

#define SSP_VERSION 8

int SSP_GetVersion();
int SSP_Init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);

// Callbacks
void SSP_SetPlaylistIndexChangedCallback(player_playlistindexchanged_cb cb, void* user);
void SSP_RemovePlaylistIndexChangedCallback();

// Properties
SSP_DEVICE* SSP_GetDevice();
void SSP_GetDeviceNew(SSP_DEVICE* device);
SSP_PLAYHEAD* SSP_GetPlayhead();
SSP_MIXER* SSP_GetMixer();

// EQ
SSP_EQPRESET* SSP_GetEQPreset();
void SSP_SetEQPreset(SSP_EQPRESET* preset);

bool SSP_GetEQBypassed();
void SSP_SetEQBypassed(bool bypassed);

// Loops
SSP_LOOP* SSP_GetLoop();
void SSP_SetLoop(SSP_LOOP* loop);

// Playback
SSP_ERROR SSP_Play();
SSP_ERROR SSP_Pause();
SSP_ERROR SSP_Stop();
SSP_ERROR SSP_Previous();
SSP_ERROR SSP_Next();
SSP_ERROR SSP_GoTo(int index);
//void SSP_GoTo(int playlistItemId); // how do we manage ids?

void SSP_Seek();
uint64_t SSP_GetPosition();
SSP_ERROR SSP_SetPosition(uint64_t position);
//void SSP_SetPosition(double positionPercentage);

// Playlist
int SSP_Playlist_AddItem(char* filePath);
int SSP_Playlist_InsertItemAt(char* filePath, int index);
int SSP_Playlist_RemoveItemAt(int index);
int SSP_Playlist_Clear();
SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index);
int SSP_Playlist_GetCount();
int SSP_Playlist_GetCurrentIndex();

// C# class:

//int BufferSize { get; set; }
//EQPreset EQPreset { get; set; }
//Loop Loop { get; }
//Device Device { get; }
//bool IsSettingPosition { get; }
//bool IsDeviceInitialized { get; }
//bool IsEQBypassed { get; }
//bool IsEQEnabled { get; }
//bool IsPaused { get; }
//bool IsPlaying { get; }
//bool IsPlayingLoop { get; }
//bool IsShuffleEnabled { get; set; }
//bool UseFloatingPoint { get; }
//int MixerSampleRate { get; }
//int CurrentSegmentIndex { get; }
//ShufflePlaylist Playlist { get; }
//RepeatType RepeatType { get; set; }
//float TimeShifting { get; set; }
//int PitchShifting { get; set; }
//int UpdatePeriod { get; set; }
//int UpdateThreads { get; set; }
//float Volume { get; set; }
//
//event LoopPlaybackStarted OnLoopPlaybackStarted;
//event LoopPlaybackStopped OnLoopPlaybackStopped;
//event PlaylistEnded OnPlaylistEnded;
//event PlaylistIndexChanged OnPlaylistIndexChanged;
//event AudioInterrupted OnAudioInterrupted;
//event BPMDetected OnBPMDetected;
//event SegmentIndexChanged OnSegmentIndexChanged;
//
//void InitializeDevice();
//void InitializeDevice(Device device, int mixerSampleRate);
//void Dispose();
//void FreeDevice();
//void FreePlugins();
//
//void Play();
//void Play(double initialPosition, bool startPaused);
//void PlayFiles(List<AudioFile> audioFiles);
//void PlayFiles(List<string> filePaths);
//void Pause();
//void Stop();
//void Previous();
//void Next();
//void GoTo(int index);
//void GoTo(Guid playlistItemId);
//
//void StartEncode(Player.EncoderType encoderType);
//void StopEncode();
//void StartCast(CastServerParams serverParams);
//void StopCast();
//
//int GetDataAvailable();
//long Seconds2Bytes(double value);
//int GetMixerData(int length, float[] sampleData);
//int GetMixerData(int length, int[] sampleData);
//long GetPosition();
//void SetPosition(double percentage);
//void SetPosition(long bytes);
//
//void ApplyEQPreset(EQPreset preset);
//void BypassEQ();
//void ResetEQ();
//void UpdateEQBand(int band, float gain, bool setCurrentEQPresetValue);
//
//void GoToMarker(Marker marker);
//void StartLoop(Loop loop);
//void UpdateLoop(Loop loop);
//void StopLoop();

#endif /* defined(__player__ssp_public__) */
