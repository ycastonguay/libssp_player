using System;
using System.IO;
using System.Timers;
using ObjCRuntime;
using UIKit;
using org.sessionsapp.player;
using System.Linq;

namespace playersampleiosxamarin
{
    public partial class PlayerViewController : UIViewController
    {
        private Timer _timerRefreshPosition;
        private static SSP_POSITION _length;

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

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
            var position = new SSP_POSITION();
            SSP.SSP_GetPosition(ref position);

            InvokeOnMainThread(() => {
                lblPosition.Text = string.Format("Position: {0} / {1}", position.str, _length.str);
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
            var item = new SSP_PLAYLISTITEM();
            int index = SSP.SSP_Playlist_GetCurrentIndex();
            int count = SSP.SSP_Playlist_GetCount();
            SSP.SSP_Playlist_GetItemAt(index, ref item);

            var length = new SSP_POSITION();
            SSP.SSP_GetPositionFromBytes(item.length, ref length);
            _length = length;

            CurrentViewController.InvokeOnMainThread(() => {
                CurrentViewController.lblPlaylist.Text = string.Format("Playlist [{0}/{1}]", index+1, count);
                CurrentViewController.lblFilePath.Text = string.Format("File path: {0}", item.filePath);
            });
        }
            
        partial void buttonPlay_TouchUpInside(UIButton sender)
        {
            SSP.SSP_Playlist_Clear();

            var documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string[] extensions = { ".mp3", ".flac", ".ape", ".wav" };
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
