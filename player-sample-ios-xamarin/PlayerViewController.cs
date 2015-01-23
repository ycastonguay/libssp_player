using System;
using System.Drawing;
using System.IO;

using Foundation;
using UIKit;
using System.Timers;

namespace playersampleiosxamarin
{
    public partial class PlayerViewController : UIViewController
    {
        private Timer _timer;

        static bool UserInterfaceIdiomIsPhone
        {
            get { return UIDevice.CurrentDevice.UserInterfaceIdiom == UIUserInterfaceIdiom.Phone; }
        }

        public PlayerViewController(IntPtr handle) : base(handle)
        {
        }

        public override void DidReceiveMemoryWarning()
        {
            // Releases the view if it doesn't have a superview.
            base.DidReceiveMemoryWarning();
			
            // Release any cached data, images, etc that aren't in use.
        }

        public override void ViewDidLoad()
        {
            base.ViewDidLoad();
			
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

            Console.WriteLine("libssp_player init successful!");

            _timer = new Timer(100);
            _timer.Elapsed += HandleTimerElapsed;
        }

        private void HandleTimerElapsed(object sender, ElapsedEventArgs e)
        {
            long position = SSP.SSP_GetPosition();

            InvokeOnMainThread(() => {
                lblPosition.Text = string.Format("Position (bytes): {0}", position);
            });
        }

        public override void ViewWillAppear(bool animated)
        {
            base.ViewWillAppear(animated);
        }

        public override void ViewDidAppear(bool animated)
        {
            base.ViewDidAppear(animated);
        }

        public override void ViewWillDisappear(bool animated)
        {
            base.ViewWillDisappear(animated);
        }

        public override void ViewDidDisappear(bool animated)
        {
            base.ViewDidDisappear(animated);
        }
            
        partial void buttonPlay_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Playlist_Clear();
            //SSP.SSP_Playlist_AddItem(

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

