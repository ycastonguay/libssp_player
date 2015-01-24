using System;
using System.Drawing;
using System.IO;
using Foundation;
using UIKit;
using System.Timers;
using ObjCRuntime;
using org.sessionsapp.player;
using System.Runtime.InteropServices;

namespace playersampleiosxamarin
{
    public partial class PlayerViewController : UIViewController
    {
        private Timer _timer;

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
            			
            _timer = new Timer(100);
            _timer.Elapsed += HandleTimerElapsed;
        }

        private void InitializePlayer()
        {
            // Perform any additional setup after loading the view, typically from a nib.
            int version = SSP.SSP_GetVersion();
            lblVersion.Text = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

            int error = SSP.SSP_Init(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                return;
            }

            //Marshal.StructureToPtr(this,
            SSP.SSP_SetPlaylistIndexChangedCallback(PlaylistIndexChanged, IntPtr.Zero);
            SSP_DEVICE device = SSP.SSP_GetDevice();

            SSP_DEVICE deviceNew = new SSP_DEVICE();
            deviceNew.name = "Test name";
            deviceNew.deviceId = 100;
            //SSP.SSP_GetDeviceNew(ref deviceNew);
            SSP.SSP_GetDeviceNew(deviceNew);

            Console.WriteLine("libssp_player init successful!");

        }

        private void HandleTimerElapsed(object sender, ElapsedEventArgs e)
        {
            long position = SSP.SSP_GetPosition();

            InvokeOnMainThread(() => {
                lblPosition.Text = string.Format("Position (bytes): {0}", position);
            });
        }

        [MonoPInvokeCallback(typeof(PlaylistIndexChangedDelegate))]
        private static void PlaylistIndexChanged(IntPtr user)
        {
            Console.WriteLine("--> PlaylistIndexChanged");

            int index = SSP.SSP_Playlist_GetCurrentIndex();
            SSP_PLAYLISTITEM item = SSP.SSP_Playlist_GetItemAt(index);

            CurrentViewController.InvokeOnMainThread(() => {
                CurrentViewController.lblFileName.Text = string.Format("{0} - {1}", index, index);
            });
        }
            
        partial void buttonPlay_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Playlist_Clear();

            var documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            var files = Directory.EnumerateFiles(documents, "*.mp3");
            foreach(var file in files)
            {
                SSP.SSP_Playlist_AddItem(file);
            }

            SSP.SSP_Play();
            _timer.Start();
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

