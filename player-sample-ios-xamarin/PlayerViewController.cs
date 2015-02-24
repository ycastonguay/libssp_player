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
using System.IO;
using System.Linq;
using System.Timers;
using ObjCRuntime;
using org.sessionsapp.player;
using UIKit;

namespace playersampleiosxamarin
{
    public partial class PlayerViewController : UIViewController
    {
        private Timer _timerRefreshPosition;
        private static SSPPosition _length;

        private LogDelegate _logDelegate;
        private StateChangedDelegate _stateChangedDelegate;
        private PlaylistIndexChangedDelegate _playlistIndexChangedDelegate;
        private AudioInterruptedDelegate _audioInterruptedDelegate;

        // TOOD: Find a way to use the IntPtr user parameter instead
        static PlayerViewController CurrentViewController { get; set; }

        static bool UserInterfaceIdiomIsPhone
        {
            get { return UIDevice.CurrentDevice.UserInterfaceIdiom == UIUserInterfaceIdiom.Phone; }
        }

        public PlayerViewController(IntPtr handle) : base(handle)
        {
        }

        public override void ViewDidLoad()
        {
            base.ViewDidLoad();

            CurrentViewController = this;
            InitializePlayer();
            			
            _timerRefreshPosition = new Timer(100);
            _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;
        }

        private void InitializePlayer()
        {
            int version = SSP.SSP_GetVersion();
            lblVersion.Text = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

            int error = SSP.SSP_Init(null);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                return;
            }

            _logDelegate = new LogDelegate(HandleLog);
            _stateChangedDelegate = new StateChangedDelegate(HandleStateChanged);
            _playlistIndexChangedDelegate = new PlaylistIndexChangedDelegate(HandlePlaylistIndexChanged);
            _audioInterruptedDelegate = new AudioInterruptedDelegate(HandleAudioInterrupted);
            SSP.SSP_SetLogCallback(_logDelegate, IntPtr.Zero);
            SSP.SSP_SetStateChangedCallback(_stateChangedDelegate, IntPtr.Zero);
            SSP.SSP_SetPlaylistIndexChangedCallback(_playlistIndexChangedDelegate, IntPtr.Zero);
            SSP.SSP_SetAudioInterruptedCallback(_audioInterruptedDelegate, IntPtr.Zero);

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init device failed with error code: {0}", error);
                return;
            }

            error = SSP.SSP_IOS_ConfigureAirPlay(true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player failed to configure AirPlay with error code: {0}", error);
                return;
            }

            error = SSP.SSP_IOS_ConfigureAudioInterruptionNotification(true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player failed to configure audio interruption notification with error code: {0}", error);
                return;
            }

            var device = new SSP_DEVICE();
            SSP.SSP_GetDevice(ref device);

            Console.WriteLine("libssp_player init successful!");
        }

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
            var position = new SSPPosition();
            SSP.SSP_GetPosition(ref position.Struct);

            InvokeOnMainThread(() => {
                lblPosition.Text = string.Format("Position: {0} / {1}", position.Str, _length.Str);
            });
        }

        [MonoPInvokeCallback(typeof(LogDelegate))]
        private static void HandleLog(IntPtr user, string str)
        {
            Console.WriteLine("libssp_player :: {0}", str);
        }

        [MonoPInvokeCallback(typeof(StateChangedDelegate))]
        private static void HandleStateChanged(IntPtr user, SSPPlayerState state)
        {
            CurrentViewController.InvokeOnMainThread(() => {
                CurrentViewController.lblState.Text = string.Format("State: {0}", state);
            });
        }

        [MonoPInvokeCallback(typeof(PlaylistIndexChangedDelegate))]
        private static void HandlePlaylistIndexChanged(IntPtr user)
        {
            var item = new SSPPlaylistItem();
            int index = SSP.SSP_Playlist_GetCurrentIndex();
            int count = SSP.SSP_Playlist_GetCount();
            SSP.SSP_Playlist_GetItemAt(index, ref item.Struct);

            var length = new SSPPosition();
            SSP.SSP_GetPositionFromBytes(item.Length, ref length.Struct);
            _length = length;

            CurrentViewController.InvokeOnMainThread(() => {
                CurrentViewController.lblPlaylist.Text = string.Format("Playlist [{0}/{1}]", index+1, count);
                CurrentViewController.lblFilePath.Text = string.Format("File path: {0}", item.FilePath);
            });
        }

        [MonoPInvokeCallback(typeof(AudioInterruptedDelegate))]
        private static void HandleAudioInterrupted(IntPtr user, bool ended)
        {
            Console.WriteLine("libssp_player -- Audio has been interrupted; ended: {0}", ended);
        }
            
        partial void buttonPlay_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Playlist_Clear();

            var documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string[] extensions = { ".mp3", ".flac", ".ape", ".wav", ".ogg", ".mpc", ".wv" };
            foreach (string file in Directory.EnumerateFiles(documents, "*.*", SearchOption.AllDirectories)
                .Where(s => extensions.Any(ext => ext == Path.GetExtension(s))))
            {
                SSP.SSP_Playlist_AddItem(file);
            }

            SSP.SSP_Play();
            _timerRefreshPosition.Start();
        }

        partial void buttonPause_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Pause();
        }

        partial void buttonStop_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Stop();
        }

        partial void buttonPrevious_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Previous();
        }

        partial void buttonNext_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Next();
        }

        private void CheckForError(int error)
        {
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("SSP Error: {0}", error);
            }
        }
    }
}
