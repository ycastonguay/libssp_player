using System;
using Gtk;
using org.sessionsapp.player;
using System.Timers;
using System.IO;
using System.Reflection;

public partial class MainWindow : Gtk.Window
{
    private Timer _timerRefreshPosition;
    private LogDelegate _logDelegate;
    private StateChangedDelegate _stateChangedDelegate;
    private PlaylistIndexChangedDelegate _playlistIndexChangedDelegate;

	public MainWindow() : base(Gtk.WindowType.Toplevel)
	{
		Build();

        _timerRefreshPosition = new Timer(100);
        _timerRefreshPosition.Elapsed += HandleTimerRefreshPositionElapsed;

        InitializePlayer();
	}
        
	protected void OnDeleteEvent(object sender, DeleteEventArgs a)
	{
		Application.Quit();
		a.RetVal = true;
	}       

    private void CheckForError(int error)
    {
        if (error != SSP.SSP_OK)
        {
            throw new Exception(string.Format("libssp_player error code: {0}", error));
        }
    }

    private void HandleTimerRefreshPositionElapsed(object sender, ElapsedEventArgs e)
    {
        var position = new SSP_POSITION();
        SSP.SSP_GetPosition(ref position);

        Gtk.Application.Invoke(delegate{
            lblPosition.Text = string.Format("Position: {0}", position.str);
        });

    }

    private void InitializePlayer()
    {
        // Perform any additional setup after loading the view, typically from a nib.
        int version = SSP.SSP_GetVersion();
        lblVersion.Text = string.Format("Version {0}", version);
        Console.WriteLine("libssp_player version: {0}", version);

        // Find plugins either in current directory (i.e. development) or in a system directory (ex: /usr/lib/Sessions or /opt/lib/Sessions)
        string pluginPath = string.Empty;
        string exePath = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);               
        if(!File.Exists(exePath + "/libbassflac.so"))
        {
            if(!File.Exists("/usr/lib/Sessions/libbassflac.so"))
            {
                if(!File.Exists("/opt/lib/Sessions/libbassflac.so"))
                {
                    throw new Exception("The BASS plugins could not be found either in the current directory, in /usr/lib/Sessions or in /opt/lib/Sessions!");
                }
                else
                {
                    pluginPath = "/opt/lib/Sessions";
                }                       
            }
            else
            {
                pluginPath = "/usr/lib/Sessions";
            }
        }
        else
        {                   
            pluginPath = exePath;
        }

        int error = SSP.SSP_Init(pluginPath);
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

        var device = new SSP_DEVICE();
        SSP.SSP_GetDevice(ref device);

        Console.WriteLine("libssp_player init successful!");
    }

    private void HandleLog(IntPtr user, string str)
    {
        Console.WriteLine("libssp_player :: {0}", str);
    }

    private void HandleStateChanged(IntPtr user, SSPPlayerState state)
    {
        Gtk.Application.Invoke(delegate{
            if(lblState != null)
                lblState.Text = string.Format("State: {0}", state);
        });
    }

    private void HandlePlaylistIndexChanged(IntPtr user)
    {
        var item = new SSP_PLAYLISTITEM();
        int index = SSP.SSP_Playlist_GetCurrentIndex();
        int count = SSP.SSP_Playlist_GetCount();
        SSP.SSP_Playlist_GetItemAt(index, ref item);

        Gtk.Application.Invoke(delegate{
            if(lblPlaylist != null)
                lblPlaylist.Text = string.Format("Playlist [{0}/{1}]", index+1, count);
            if(lblFilePath != null)
                lblFilePath.Text = string.Format("File path: {0}", item.filePath);
        });
    }

    protected void OnBtnPlayClicked(object sender, EventArgs e)
    {
        CheckForError(SSP.SSP_Play());

        if(!_timerRefreshPosition.Enabled)
            _timerRefreshPosition.Start();
    }

    protected void OnBtnPauseClicked(object sender, EventArgs e)
    {
        CheckForError(SSP.SSP_Pause());
    }

    protected void OnBtnStopClicked(object sender, EventArgs e)
    {
        CheckForError(SSP.SSP_Stop());

        if(_timerRefreshPosition.Enabled)
            _timerRefreshPosition.Stop();
    }

    protected void OnBtnPreviousClicked(object sender, EventArgs e)
    {
        CheckForError(SSP.SSP_Previous());
    }

    protected void OnBtnNextClicked(object sender, EventArgs e)
    {
        CheckForError(SSP.SSP_Next());
    }

    protected void OnBtnOpenAudioFilesClicked(object sender, EventArgs e)
    {
        Gtk.FileChooserDialog dialog = 
            new Gtk.FileChooserDialog("Select audio files to play.", 
                this, FileChooserAction.Open, 
                "Cancel", ResponseType.Cancel, 
                "Choose audio files to play", ResponseType.Accept);

        dialog.SelectMultiple = true;
        if (dialog.Run() == (int)ResponseType.Accept)
        {
            SSP.SSP_Playlist_Clear();

            foreach (var filename in dialog.Filenames)
            {
                SSP.SSP_Playlist_AddItem(filename);
            }
        }

        dialog.Destroy();
    }

    protected void OnBtnCloseClicked(object sender, EventArgs e)
    {
        if (SSP.SSP_GetState() == SSPPlayerState.Playing ||
            SSP.SSP_GetState() == SSPPlayerState.Paused)
        {
            CheckForError(SSP.SSP_Stop());
        }
        CheckForError(SSP.SSP_Free());

        Application.Quit();
    }
}
