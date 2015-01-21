//
//  sspPlayer.h
//  sspPlayer
//
//  Created by Yanick Castonguay on 2015-01-19.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#ifndef player_ssp_player____FILEEXTENSION___
#define player_ssp_player____FILEEXTENSION___

#include <stdbool.h>
#include "ssp_errors.h"
#include "ssp_structs.h"
#include "ssp_callbacks.h"

//SSP_PLAYER* player_create();
//void player_free(SSP_PLAYER* sspPlayer);

int SSP_Init(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);

// Properties


int SSP_GetVolume();
void SSP_SetVolume(int volume);

// EQ
SSP_EQPRESET* SSP_GetEQPreset();
void SSP_SetEQPreset(SSP_EQPRESET* preset);

bool SSP_GetEQBypassed();
void SSP_SetEQBypassed(bool bypassed);

// Loops

// Playback
SSP_ERROR SSP_Play();
SSP_ERROR SSP_Pause();
SSP_ERROR SSP_Stop();
SSP_ERROR SSP_Previous();
SSP_ERROR SSP_Next();
SSP_ERROR SSP_GoTo(int index);
//void SSP_GoTo(int playlistItemId); // how do we manage ids?

void SSP_Seek();
long SSP_GetPosition();
void SSP_SetPosition(long positionBytes);
//void SSP_SetPosition(double positionPercentage);

// Playlist
int SSP_Playlist_AddItem(char* filePath);
int SSP_Playlist_InsertItemAt(char* filePath, int index);
int SSP_Playlist_RemoveItemAt(int index);
int SSP_Playlist_RemoveItems();
//SSP_PLAYLISTITEM* SSP_Playlist_GetItemAt(int index);
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

#endif
