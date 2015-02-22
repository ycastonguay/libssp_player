using System;
using System.Timers;
using System.Windows;
using System.Windows.Threading;
using org.sessionsapp.player;

namespace player_sample_win32_wpf
{
    public partial class MainWindow : Window
    {
        private Timer _timerRefreshPosition;
        private LogDelegate _logDelegate;
        private StateChangedDelegate _stateChangedDelegate;
        private PlaylistIndexChangedDelegate _playlistIndexChangedDelegate;

        public MainWindow()
        {
            InitializeComponent();
            InitializePlayer();

            _timerRefreshPosition = new Timer();
            _timerRefreshPosition.Interval = 100;
            _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;
        }

        private void InitializePlayer()
        {
            int version = SSP.SSP_GetVersion();
            lblVersion.Content = string.Format("Version {0}", version);
            Console.WriteLine("libssp_player version: {0}", version);

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

            try
            {
                var mixer = new SSP_MIXER();
                SSP.SSP_GetMixer(ref mixer);

                // crashes, probably because of the const char*
                //var device = new SSP_DEVICE();
                //device.name = "hello";
                //SSP.SSP_GetDevice(ref device);
                //string test = Marshal.PtrToStringAnsi(device.name);
                var device = new SSPDevice();
                //device.Struct.name = "testy";
                device.Name = "hello";
                SSP.SSP_GetDevice(ref device.Struct);
                Console.WriteLine("Device is {0}", device.Name);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: {0}", ex);
            }

            Console.WriteLine("libssp_player init successful!");
        }

        private void CheckForError(int error)
        {
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("SSP Error {0}", error);
                throw new Exception(string.Format("libssp_player error code: {0}", error));
            }
        }

        private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
        {
            var position = new SSP_POSITION();
            SSP.SSP_GetPosition(ref position);

            Dispatcher.BeginInvoke(DispatcherPriority.Background, new Action(() =>
            {
                lblPosition.Content = string.Format("Position: {0}", position.str);
            }));
        }

        private void HandleLog(IntPtr user, string str)
        {
            Console.WriteLine("libssp_player :: {0}", str);
        }

        private void HandleStateChanged(IntPtr user, SSPPlayerState state)
        {
            Dispatcher.BeginInvoke(DispatcherPriority.Background, new Action(() =>
            {
                if (lblState != null)
                    lblState.Content = string.Format("State: {0}", state);
            }));
        }

        private void HandlePlaylistIndexChanged(IntPtr user)
        {
            // crashes, probably because of const char *
            //var item = new SSP_PLAYLISTITEM();
            //int index = SSP.SSP_Playlist_GetCurrentIndex();
            //int count = SSP.SSP_Playlist_GetCount();
            //SSP.SSP_Playlist_GetItemAt(index, ref item);

            //Dispatcher.BeginInvoke(DispatcherPriority.Background, new Action(() =>
            //{
            //    if (lblPlaylist != null)
            //        lblPlaylist.Content = string.Format("Playlist [{0}/{1}]", index + 1, count);
            //    if (lblFilePath != null)
            //        lblFilePath.Content = string.Format("File path: {0}", item.filePath);
            //}));
        }

        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new System.Windows.Forms.OpenFileDialog();
            dialog.Filter = "Audio files (*.mp3,*.flac,*.ogg, *.ape)|*.mp3;*.flac;*.ogg;*.ape";
            dialog.Multiselect = true;
            dialog.Title = "Select audio files to play";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                SSP.SSP_Playlist_Clear();

                foreach (var filename in dialog.FileNames)
                {
                    SSP.SSP_Playlist_AddItem(filename);
                }
            }
        }

        private void btnClose_Click(object sender, RoutedEventArgs e)
        {
            if (_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Stop();

            if (SSP.SSP_GetState() == SSPPlayerState.Playing ||
               SSP.SSP_GetState() == SSPPlayerState.Paused)
                SSP.SSP_Stop();

            SSP.SSP_Free();
            Application.Current.Shutdown();
        }

        private void btnPlay_Click(object sender, RoutedEventArgs e)
        {
            CheckForError(SSP.SSP_Play());

            if (!_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Start();
        }

        private void btnPause_Click(object sender, RoutedEventArgs e)
        {
            CheckForError(SSP.SSP_Pause());
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            CheckForError(SSP.SSP_Stop());

            if (_timerRefreshPosition.Enabled)
                _timerRefreshPosition.Stop();
        }

        private void btnPrevious_Click(object sender, RoutedEventArgs e)
        {
            CheckForError(SSP.SSP_Previous());
        }

        private void btnNext_Click(object sender, RoutedEventArgs e)
        {
            CheckForError(SSP.SSP_Previous());
        }
    }
}
