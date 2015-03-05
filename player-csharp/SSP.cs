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

using System;
using System.Runtime.InteropServices;

namespace org.sessionsapp.player
{
    public static class SSP
    {
#if IOS
        public const string DllImportValue = "__Internal";
#elif ANDROID || LINUX
        public const string DllImportValue = "libssp_player.so";
#elif OSX || MACOSX
        public const string DllImportValue = "libssp_player.dylib";
#else
        public const string DllImportValue = "libssp_player.dll";
#endif

        // TODO: Check for usage of uint16_t, uint32_t and uint64_t and make sure the types are unsigned in this class
        // Initialization
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetVersion();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Init(string pathForPlugins);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_FreeDevice();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Free();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern SSPPlayerState SSP_GetState();

        // iOS-only
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_IOS_ConfigureAirPlay(bool enable);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_IOS_ConfigureAudioInterruptionNotification(bool enable);

        //[DllImport(DllImportValue, CharSet = CharSet.Ansi, EntryPoint = "SSP_GetDevice", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void SSP_GetDevice([In, Out] ref SSP_DEVICE device);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_GetDevice(ref SSP_DEVICE device);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_GetMixer(ref SSP_MIXER mixer);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetBufferSize(int bufferSize);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetUpdatePeriod(int updatePeriod);

        // EQ
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_GetEQPreset(ref SSP_EQPRESET preset);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetEQPreset(ref SSP_EQPRESET preset);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetEQPresetBand(int band, float gain);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_ResetEQPreset(ref SSP_EQPRESET preset);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SSP_GetEQEnabled();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetEQEnabled(bool enabled);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_ResetEQ();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_NormalizeEQ();

        // Loops
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StartLoop(ref SSP_LOOP loop);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_UpdateLoop(ref SSP_LOOP loop);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StopLoop();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_GetLoop(ref SSP_LOOP loop);

        // Playback
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Play();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_PlayWithOptions(int startIndex, long startPosition, bool startPaused);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Pause();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Stop();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Previous();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Next();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GoTo(int index);

        // Playhead
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SSP_GetIsShuffle();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetIsShuffle(bool shuffle);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern SSPRepeatType SSP_GetRepeatType();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetRepeatType(SSPRepeatType repeat);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_ToggleRepeatType();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern float SSP_GetVolume();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetVolume(float volume);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern float SSP_GetTimeShifting();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetTimeShifting(float timeShifting);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetPitchShifting();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetPitchShifting(int pitchShifting);

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SSP_GetIsSettingPosition();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SSP_GetIsPlayingLoop();

        // Position
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetPosition(ref SSP_POSITION position);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetPosition(long position);       
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_SetPositionPercentage(float position);      
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetPositionFromBytes(long bytes, ref SSP_POSITION position);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetPositionFromPercentage(float percentage, ref SSP_POSITION position);

        // Data
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern long SSP_GetBytesFromSecondsForCurrentChannel(float seconds);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetMixerData(float[] buffer, int length);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetMixerData(int[] buffer, int length);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern long SSP_GetDataAvailable();

        // Encoder
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StartEncode(SSPEncoderType encoder);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StopEncode();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StartCast(SSP_CAST_SERVER server);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_StopCast();

        // Device detection
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_GetOutputDeviceCount();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SSP_GetOutputDevice(int index, ref SSP_DEVICE device);

        // Playlist
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_AddItem([MarshalAsAttribute(UnmanagedType.LPStr)] string filePath);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_InsertItemAt([MarshalAsAttribute(UnmanagedType.LPStr)] string filePath, int index);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_RemoveItemAt(int index);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_Clear();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_GetItemAt(int index, ref SSP_PLAYLISTITEM item);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_GetCount();
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Playlist_GetCurrentIndex();

        // Decoder
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 SSP_Decoder_CreateStream([MarshalAsAttribute(UnmanagedType.LPStr)] string filePath, bool useFloatingPoint);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SSP_Decoder_FreeStream(UInt32 handle);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern ulong SSP_Decoder_GetLength(UInt32 handle);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern ulong SSP_Decoder_GetData(float[] buffer, int length);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern ulong SSP_Decoder_GetData(int[] buffer, int length);

        // Callbacks
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetPlaylistIndexChangedCallback(PlaylistIndexChangedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemovePlaylistIndexChangedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetPlaylistEndedCallback(PlaylistEndedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemovePlaylistEndedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetStateChangedCallback(StateChangedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveStateChangedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetLogCallback(LogDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveLogCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetLoopPlaybackStartedCallback(LoopPlaybackStartedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveLoopPlaybackStartedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetLoopPlaybackStoppedCallback(LoopPlaybackStoppedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveLoopPlaybackStoppedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetAudioInterruptedCallback(AudioInterruptedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveAudioInterruptedCallback();

        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_SetBPMDetectedCallback(BPMDetectedDelegate callback, IntPtr user);
        [DllImport(DllImportValue, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SSP_RemoveBPMDetectedCallback();

        // Errors
        public static int SSP_OK = 0;
        public static int SSP_ERROR_UNKNOWN = 1;
    }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void PlaylistIndexChangedDelegate(IntPtr user);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void PlaylistEndedDelegate(IntPtr user);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void StateChangedDelegate(IntPtr user, SSPPlayerState state);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LogDelegate(IntPtr user, string str);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LoopPlaybackStartedDelegate(IntPtr user);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LoopPlaybackStoppedDelegate(IntPtr user);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void AudioInterruptedDelegate(IntPtr user, bool ended);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void BPMDetectedDelegate(IntPtr user, float bpm);

    public enum SSPPlayerState
    {
        Uninitialized = 0,
        Initialized = 1,
        Stopped = 2,
        Playing = 3,
        Paused = 4
    }

    public enum SSPRepeatType
    {
        Off = 0,
        Playlist = 1,
        Song = 2
    }

    public enum SSPEncoderType
    {
        OGG = 0,
        AAC = 1,
        MP3 = 2
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_CAST_SERVER
    {
        public IntPtr name;
        public IntPtr url;
        public IntPtr password;
        public int bitrate;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_MIXER
    {
        public int sampleRate;
        public int bufferSize;
        public int updatePeriod;
        public bool useFloatingPoint;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_EQPRESETBAND
    {
        public float center;
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string label;
        public float bandwidth;
        public float gain;
        public float q;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_EQPRESET
    {
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 38)]
        public string id;
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string name;
        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 18)]
        public SSP_EQPRESETBAND[] bands;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_LOOP
    {
        public long startPosition;
        public long endPosition;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_POSITION
    {
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string str;
        public long bytes;
        public long ms;
        public long samples;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_DEVICE
    {
        public IntPtr name;
        public IntPtr driver;
        public int deviceId;
        public bool isInitialized;
        public bool isDefault;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_PLAYLISTITEM
    {
        public bool isLoaded;
        public IntPtr filePath;
        public int sampleRate;
        public int numberOfChannels;
        public int bitsPerSample;
        public int channel;
        public long length;
    }
}
