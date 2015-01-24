
using System;
using System.Collections.Generic;
using System.Linq;
using MonoMac.Foundation;
using MonoMac.AppKit;
using org.sessionsapp.player;

namespace playersampleosxxamarin
{
    public partial class MainWindowController : MonoMac.AppKit.NSWindowController
    {
        #region Constructors

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
            InitializePlayer();
        }

        private void InitializePlayer()
        {
            // Perform any additional setup after loading the view, typically from a nib.
            int version = SSP.SSP_GetVersion();
            //lblVersion.Text = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

            int error = SSP.SSP_Init(-1, 44100, 1000, 100, true);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player init failed with error code: {0}", error);
                return;
            }

            //Marshal.StructureToPtr(this,
            //SSP.SSP_SetPlaylistIndexChangedCallback(PlaylistIndexChanged, IntPtr.Zero);
            SSP_DEVICE device = SSP.SSP_GetDevice();

            SSP_DEVICE deviceNew = new SSP_DEVICE();
            deviceNew.name = "Test name";
            deviceNew.deviceId = 100;
            //SSP.SSP_GetDeviceNew(ref deviceNew);
            SSP.SSP_GetDeviceNew(deviceNew);

            Console.WriteLine("libssp_player init successful!");

        }


        #endregion

        //strongly typed window accessor
        public new MainWindow Window
        {
            get
            {
                return (MainWindow)base.Window;
            }
        }
    }
}

