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
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using System.Timers;
using org.sessionsapp.player;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace playersampleandroidxamarin
{
    [Activity(Label = "libssp_player", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        private Timer _timerRefreshPosition;
        private LogDelegate _logDelegate;
        private StateChangedDelegate _stateChangedDelegate;
        private PlaylistIndexChangedDelegate _playlistIndexChangedDelegate;

        private TextView _lblVersion;
        private TextView _lblState;
        private TextView _lblPlaylist;
        private TextView _lblFilePath;
        private TextView _lblPosition;
        private Button _btnPlay;
        private Button _btnPause;
        private Button _btnStop;
        private Button _btnPrevious;
        private Button _btnNext;

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            SetContentView(Resource.Layout.Main);

            _lblVersion = FindViewById<TextView>(Resource.Id.lblVersion);
            _lblState = FindViewById<TextView>(Resource.Id.lblState);
            _lblPlaylist = FindViewById<TextView>(Resource.Id.lblPlaylist);
            _lblFilePath = FindViewById<TextView>(Resource.Id.lblFilePath);
            _lblPosition = FindViewById<TextView>(Resource.Id.lblPosition);

            _btnPlay = FindViewById<Button>(Resource.Id.btnPlay);
            _btnPlay.Click += HandleBtnPlayClick;
            _btnPause = FindViewById<Button>(Resource.Id.btnPause);
            _btnPause.Click += HandleBtnPauseClick;
            _btnStop = FindViewById<Button>(Resource.Id.btnStop);
            _btnStop.Click += HandleBtnStopClick;
            _btnPrevious = FindViewById<Button>(Resource.Id.btnPrevious);
            _btnPrevious.Click += HandleBtnPreviousClick;
            _btnNext = FindViewById<Button>(Resource.Id.btnNext);
            _btnNext.Click += HandleBtnNextClick;

            InitializePlayer();
            LoadAudioFiles();

            _timerRefreshPosition = new Timer();
            _timerRefreshPosition.Interval = 100;
            _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;
        }

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
            var position = new SSPPosition();
            SSP.SSP_GetPosition(ref position.Struct);

            RunOnUiThread(() => {
                _lblPosition.Text = string.Format("Position: {0}", position.Str);
            });
        }
            
        private void InitializePlayer()
        {
            // Load dynamic libraries
            Java.Lang.JavaSystem.LoadLibrary("bass");
            Java.Lang.JavaSystem.LoadLibrary("bass_fx");
            Java.Lang.JavaSystem.LoadLibrary("bassmix");
            Java.Lang.JavaSystem.LoadLibrary("bassenc");
            Java.Lang.JavaSystem.LoadLibrary("ssp_player");

            // Perform any additional setup after loading the view, typically from a nib.
            int version = SSP.SSP_GetVersion();
            _lblVersion.Text = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

            string path = ApplicationInfo.NativeLibraryDir;
            int error = SSP.SSP_Init(path);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                CheckForError(error);
                return;
            }

            _logDelegate = new LogDelegate(HandleLog);
            _stateChangedDelegate = new StateChangedDelegate(HandleStateChanged);
            _playlistIndexChangedDelegate = new PlaylistIndexChangedDelegate(HandlePlaylistIndexChanged);
            SSP.SSP_SetLogCallback(_logDelegate, IntPtr.Zero);
            SSP.SSP_SetStateChangedCallback(_stateChangedDelegate, IntPtr.Zero);
            SSP.SSP_SetPlaylistIndexChangedCallback(_playlistIndexChangedDelegate, IntPtr.Zero);

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, false);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init device failed with error code: {0}", error);
                CheckForError(error);
                return;
            }

            var device = new SSPDevice();
            SSP.SSP_GetDevice(ref device.Struct);

            int deviceCount = SSP.SSP_GetOutputDeviceCount();
            var devices = new List<SSPDevice>();
            for (int a = 0; a < deviceCount; a++)
            {
                var newDevice = new SSPDevice();
                SSP.SSP_GetOutputDevice(a, ref newDevice.Struct);
                devices.Add(newDevice);
            }

            Console.WriteLine("libssp_player init successful!");
        }

        private void LoadAudioFiles()
        {
            SSP.SSP_Playlist_Clear();
            var musicFolder = global::Android.OS.Environment.GetExternalStoragePublicDirectory(global::Android.OS.Environment.DirectoryMusic).ToString();
            string[] extensions = { ".mp3", ".flac", ".ape", ".wav", ".ogg", ".mpc", ".wv" };
            var files = Directory.EnumerateFiles(musicFolder, "*.*", SearchOption.AllDirectories)
                .Where(s => extensions.Any(ext => ext == Path.GetExtension(s)));
            foreach (string file in files)
            {
                Console.WriteLine("File: {0}", file);
                SSP.SSP_Playlist_AddItem(file);
            }
        }

        private void CheckForError(int error)
        {
            if (error != SSP.SSP_OK)
            {
                throw new Exception(string.Format("libssp_player error code: {0}", error));
            }
        }

        private void HandleLog(IntPtr user, string str)
        {
            Console.WriteLine("libssp_player :: {0}", str);
        }

        private void HandleStateChanged(IntPtr user, SSPPlayerState state)
        {            
            RunOnUiThread(() => {
                _lblState.Text = string.Format("State: {0}", state);
            });
        }

        private void HandlePlaylistIndexChanged(IntPtr user)
        {
            int index = SSP.SSP_Playlist_GetCurrentIndex();
            int count = SSP.SSP_Playlist_GetCount();
            var item = new SSPPlaylistItem();
            SSP.SSP_Playlist_GetItemAt(index, ref item.Struct);

            RunOnUiThread(() => {
                _lblPlaylist.Text = string.Format("Playlist [{0}/{1}]", index+1, count);
                _lblFilePath.Text = string.Format("File path: {0}", item.FilePath);
            });
        }

        private void HandleBtnPlayClick(object sender, EventArgs e)
        {
            CheckForError(SSP.SSP_Play());

            if(!_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Start();  
        }

        private void HandleBtnPauseClick(object sender, EventArgs e)
        {
            CheckForError(SSP.SSP_Pause());
        }

        private void HandleBtnStopClick(object sender, EventArgs e)
        {
            CheckForError(SSP.SSP_Stop());

            if(_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Stop();
        }

        private void HandleBtnPreviousClick(object sender, EventArgs e)
        {
            CheckForError(SSP.SSP_Previous());
        }

        private void HandleBtnNextClick(object sender, EventArgs e)
        {
            CheckForError(SSP.SSP_Next());
        }

    }
}
