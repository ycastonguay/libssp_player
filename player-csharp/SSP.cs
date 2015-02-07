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
#elif ANDROID
        public const string DllImportValue = "libssp_player.so";
#elif OSX
        public const string DllImportValue = "libssp_player.dylib";
#endif

        [DllImport (DllImportValue)]
        public static extern int SSP_GetVersion();
        [DllImport (DllImportValue)]
        public static extern int SSP_Init(string pathForPlugins);
        [DllImport (DllImportValue)]
        public static extern int SSP_Free();
        [DllImport (DllImportValue)]
        public static extern int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
        [DllImport (DllImportValue)]
        public static extern int SSP_FreeDevice();

        [DllImport(DllImportValue, CharSet = CharSet.Ansi, EntryPoint = "SSP_GetDevice")]
        public static extern void SSP_GetDevice(ref SSP_DEVICE device);
        //public static extern void SSP_GetDeviceNew([In, Out] SSP_DEVICE device);

        [DllImport (DllImportValue)]
        public static extern long SSP_GetPosition();
        //[DllImport (DllImportValue)]
        [DllImport(DllImportValue, CharSet = CharSet.Ansi, EntryPoint = "SSP_GetPositionNew")]
        public static extern int SSP_GetPositionNew(ref SSP_POSITION position);
        [DllImport (DllImportValue)]
        public static extern int SSP_SetPosition(long position);

        [DllImport (DllImportValue)]
        public static extern int SSP_Play();
        [DllImport (DllImportValue)]
        public static extern int SSP_Pause();
        [DllImport (DllImportValue)]
        public static extern int SSP_Stop();
        [DllImport (DllImportValue)]
        public static extern int SSP_Previous();
        [DllImport (DllImportValue)]
        public static extern int SSP_Next();
        [DllImport (DllImportValue)]
        public static extern int SSP_GoTo(int index);

        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_AddItem(string filePath);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_InsertItemAt(string filePath, int index);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_RemoveItemAt(int index);
        [DllImport (DllImportValue)]
        public static extern SSP_PLAYLISTITEM SSP_Playlist_GetItemAt(int index);
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_Clear();
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_GetCount();
        [DllImport (DllImportValue)]
        public static extern int SSP_Playlist_GetCurrentIndex();

        // Callbacks
        [DllImport (DllImportValue)]
        public static extern void SSP_SetPlaylistIndexChangedCallback(PlaylistIndexChangedDelegate callback, IntPtr user);
        [DllImport (DllImportValue)]
        public static extern void SSP_RemovePlaylistIndexChangedCallback();
        [DllImport (DllImportValue)]
        public static extern void SSP_SetLogCallback(LogDelegate callback, IntPtr user);
        [DllImport (DllImportValue)]
        public static extern void SSP_RemoveLogCallback();

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

    public enum SSPPlayerState
    {
        Unknown = 0,
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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_POSITION
    {
        public string str;
        public long bytes;
        public long ms;
        public long samples;
    }
        
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_DEVICE
    {
        public string name;
        public int deviceId;
        public bool isInitialized;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SSP_PLAYLISTITEM
    {
        public bool isLoaded;
        public string filePath;
        public int sampleRate;
        public int numberOfChannels;
        public uint channel;
        public long length;
    }
}
