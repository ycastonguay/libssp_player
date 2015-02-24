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
using org.sessionsapp.player;
using System.Timers;

namespace playersampleandroidxamarin
{
    [Activity(Label = "libssp_player", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        private Timer _timerRefreshPosition;
        private LogDelegate _logDelegate;
        private StateChangedDelegate _stateChangedDelegate;
        private PlaylistIndexChangedDelegate _playlistIndexChangedDelegate;

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            SetContentView(Resource.Layout.Main);
            Button button = FindViewById<Button>(Resource.Id.myButton);
            button.Click += delegate
            {
                //button.Text = string.Format("{0} clicks!", count++);
            };

            InitializeBASS();
            //InitializePlayer();

            _timerRefreshPosition = new Timer();
            _timerRefreshPosition.Interval = 100;
            _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;
        }

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
//            var position = new SSPPosition();
//            SSP.SSP_GetPosition(ref position.Struct);
//
//            InvokeOnMainThread(() => {
//                lblPosition.StringValue = string.Format("Position: {0}", position.Str);
//            });
        }

        private void InitializeBASS()
        {
            Console.WriteLine("libssp_player - Initializing BASS test...");
            int success = BASS.BASS_Init(-1, 44100);
            Console.WriteLine("libssp_player - Initializing BASS test (success: {0})... DONE!", success);
        }

//        private void InitializePlayer()
//        {
//            int version = SSP.SSP_GetVersion();
//            Console.WriteLine("libssp_player - Version: {0}", version);
//
//            Console.WriteLine("libssp_player - Initializing player...");
//            int error = SSP.SSP_Init(string.Empty);
//            if (error != SSP.SSP_OK)
//            {
//                Console.WriteLine("libssp_player - SSP_Init error code: {0}", error);
//                return;
//            }
//
//            Console.WriteLine("libssp_player - Initializing device...");
//            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, false);
//            if (error != SSP.SSP_OK)
//            {
//                Console.WriteLine("libssp_player - SSP_InitDevice error code: {0}", error);
//                return;
//            }
//
//            Console.WriteLine("libssp_player - Init successful!");
//        }

        private void InitializePlayer()
        {
            // Perform any additional setup after loading the view, typically from a nib.
            int version = SSP.SSP_GetVersion();
            //lblVersion.StringValue = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

//            // Try to get the plugins in the current path
//            string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
//            string pluginPath = exePath.Replace("MonoBundle", "Resources");
//            if(!File.Exists(pluginPath + "/libbassflac.dylib"))
//            {
//                throw new Exception("The BASS plugins could not be found in the current directory!");
//            }

            int error = SSP.SSP_Init(string.Empty);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                return;
            }

            _logDelegate = new LogDelegate(HandleLog);
            _stateChangedDelegate = new StateChangedDelegate(HandleStateChanged);
            _playlistIndexChangedDelegate = new PlaylistIndexChangedDelegate(HandlePlaylistIndexChanged);
            SSP.SSP_SetLogCallback(_logDelegate, IntPtr.Zero);
            SSP.SSP_SetStateChangedCallback(_stateChangedDelegate, IntPtr.Zero);
            SSP.SSP_SetPlaylistIndexChangedCallback(_playlistIndexChangedDelegate, IntPtr.Zero);

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init device failed with error code: {0}", error);
                return;
            }

//            var device = new SSPDevice();
//            SSP.SSP_GetDevice(ref device.Struct);

            Console.WriteLine("libssp_player init successful!");
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
//            InvokeOnMainThread(() => {
//                if(lblState != null)
//                    lblState.StringValue = string.Format("State: {0}", state);
//            });
        }

        private void HandlePlaylistIndexChanged(IntPtr user)
        {
//            int index = SSP.SSP_Playlist_GetCurrentIndex();
//            int count = SSP.SSP_Playlist_GetCount();
//            var item = new SSPPlaylistItem();
//            SSP.SSP_Playlist_GetItemAt(index, ref item.Struct);
//
//            InvokeOnMainThread(() => {
//                if(lblPlaylist != null)
//                    lblPlaylist.StringValue = string.Format("Playlist [{0}/{1}]", index+1, count);
//                if(lblFilePath != null)
//                    lblFilePath.StringValue = string.Format("File path: {0}", item.FilePath);
//            });
        }
    }
}
