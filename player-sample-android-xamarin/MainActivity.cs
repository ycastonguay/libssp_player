using System;

using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using org.sessionsapp.player;

namespace playersampleandroidxamarin
{
    [Activity(Label = "player-sample-android-xamarin", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        int count = 1;

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            // Get our button from the layout resource,
            // and attach an event to it
            Button button = FindViewById<Button>(Resource.Id.myButton);

            //InitializeBASS();
            InitializePlayer();			

            button.Click += delegate
            {
                button.Text = string.Format("{0} clicks!", count++);
            };
        }

        private void InitializeBASS()
        {
            Console.WriteLine("libssp_player - Initializing BASS test...");
            int success = BASS.BASS_Init(-1, 44100);
            Console.WriteLine("libssp_player - Initializing BASS test (success: {0})... DONE!", success);
        }

        private void InitializePlayer()
        {
            int version = SSP.SSP_GetVersion();
            Console.WriteLine("libssp_player - Version: {0}", version);

            Console.WriteLine("libssp_player - Initializing player...");
            int error = SSP.SSP_Init();
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player - SSP_Init error code: {0}", error);
                return;
            }

            Console.WriteLine("libssp_player - Initializing device...");
            error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, false);
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("libssp_player - SSP_InitDevice error code: {0}", error);
                return;
            }

            Console.WriteLine("libssp_player - Init successful!");
        }
    }
}


