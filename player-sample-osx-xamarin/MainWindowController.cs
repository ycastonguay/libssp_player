﻿// Copyright © 2011-2015 Yanick Castonguay
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
using System.Collections.Generic;
using System.Linq;
using MonoMac.Foundation;
using MonoMac.AppKit;
using org.sessionsapp.player;
using System.IO;
using System.Reflection;
using System.Timers;

namespace playersampleosxxamarin
{
    public partial class MainWindowController : MonoMac.AppKit.NSWindowController
    {
        private Timer _timerRefreshPosition;

        //strongly typed window accessor
        public new MainWindow Window
        {
            get
            {
                return (MainWindow)base.Window;
            }
        }

        // Called when created from unmanaged code
        public MainWindowController(IntPtr handle) : base(handle)
        {
            Initialize();
        }
		
        // Called when created directly from a XIB file
        [Export("initWithCoder:")]
        public MainWindowController(NSCoder coder) : base(coder)
        {
            Initialize();
        }
		
        // Call to load from the XIB/NIB file
        public MainWindowController() : base("MainWindow")
        {
            Initialize();
        }
		
        // Shared initialization code
        void Initialize()
        {
            _timerRefreshPosition = new Timer();
            _timerRefreshPosition.Interval = 100;
            _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;
        }

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
            var position = new SSP_POSITION();
            SSP.SSP_GetPositionNew(ref position);

            InvokeOnMainThread(() => {
                lblPosition.StringValue = string.Format("Position: {0}", position.str);
            });
        }

        public override void WindowDidLoad()
        {
            base.WindowDidLoad();
            InitializePlayer();
        }

        private void InitializePlayer()
        {
            // Perform any additional setup after loading the view, typically from a nib.
            int version = SSP.SSP_GetVersion();
            lblVersion.StringValue = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

            // Try to get the plugins in the current path
            string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string pluginPath = exePath.Replace("MonoBundle", "Resources");
            if(!File.Exists(pluginPath + "/libbassflac.dylib"))
            {
                throw new Exception("The BASS plugins could not be found in the current directory!");
            }

            int error = SSP.SSP_Init(pluginPath);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                return;
            }

            SSP.SSP_SetLogCallback(HandleLog, IntPtr.Zero);
            SSP.SSP_SetStateChangedCallback(HandleStateChanged, IntPtr.Zero);
            SSP.SSP_SetPlaylistIndexChangedCallback(HandlePlaylistIndexChanged, IntPtr.Zero);

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init device failed with error code: {0}", error);
                return;
            }

            var device = new SSP_DEVICE();
            SSP.SSP_GetDevice(ref device);

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
            InvokeOnMainThread(() => {
                if(lblState != null)
                    lblState.StringValue = string.Format("State: {0}", state);
            });
        }

        private void HandlePlaylistIndexChanged(IntPtr user)
        {
            var item = new SSP_PLAYLISTITEM();
            int index = SSP.SSP_Playlist_GetCurrentIndex();
            int count = SSP.SSP_Playlist_GetCount();
            SSP.SSP_Playlist_GetItemAtNew(index, ref item);

            InvokeOnMainThread(() => {
                if(lblPlaylist != null)
                    lblPlaylist.StringValue = string.Format("Playlist [{0}/{1}]", index+1, count);
                if(lblFilePath != null)
                    lblFilePath.StringValue = string.Format("File path: {0}", item.filePath);
            });
        }

        partial void actionClose(NSObject sender)
        {
            if(_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Stop();

            if(SSP.SSP_GetState() != SSPPlayerState.Stopped)
                SSP.SSP_Stop();
            
            SSP.SSP_Free();
            NSApplication.SharedApplication.Terminate(this);
        }

        partial void actionOpenAudioFiles(NSObject sender)
        {
            var panel = new NSOpenPanel();
            panel.AllowsMultipleSelection = true;
            panel.CanChooseDirectories = false;
            panel.CanChooseFiles = true;
            panel.FloatingPanel = true;
            panel.AllowedFileTypes = new string[3] { "mp3", "wav", "flac" };

            SSP.SSP_Playlist_Clear();

            if(panel.RunModal() == 0)
                return;

            foreach(var url in panel.Urls)
            {
                SSP.SSP_Playlist_AddItem(url.Path);
            }
        }

        partial void actionPlay(NSObject sender)
        {
            CheckForError(SSP.SSP_Play());

            if(!_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Start();
        }

        partial void actionPause(NSObject sender)
        {
            CheckForError(SSP.SSP_Pause());
        }

        partial void actionStop(NSObject sender)
        {
            CheckForError(SSP.SSP_Stop());

            if(_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Stop();
        }

        partial void actionPrevious(NSObject sender)
        {
            CheckForError(SSP.SSP_Previous());
        }

        partial void actionNext(NSObject sender)
        {
            CheckForError(SSP.SSP_Next());
        }
    }
}
