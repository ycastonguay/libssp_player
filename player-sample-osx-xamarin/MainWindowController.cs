
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
        }

        public override void WindowDidLoad()
        {
            base.WindowDidLoad();
            InitializePlayer();
        }

        public void HandleLog(IntPtr user, string str)
        {
            Console.WriteLine("libssp_player :: {0}", str);
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

            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init device failed with error code: {0}", error);
                return;
            }

            var device = new SSP_DEVICE();
            device.name = "testy";
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

        partial void actionClose(NSObject sender)
        {
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
            _timerRefreshPosition.Start();
        }

        partial void actionPause(NSObject sender)
        {
            CheckForError(SSP.SSP_Pause());
        }

        partial void actionStop(NSObject sender)
        {
            CheckForError(SSP.SSP_Stop());
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
