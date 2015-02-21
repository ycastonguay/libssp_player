using System;
using Gtk;
using org.sessionsapp.player;

public partial class MainWindow : Gtk.Window
{
	public MainWindow() : base(Gtk.WindowType.Toplevel)
	{
		Build();

        //int version = BASS.BASS_GetVersion();
        //Console.WriteLine("BASS version {0}", version);
        //int error = BASS.BASS_Init(-1, 44100);

        int sspVersion = SSP.SSP_GetVersion();
        Console.WriteLine("libssp_player version {0}", sspVersion);
        CheckForError(SSP.SSP_Init(string.Empty));
        CheckForError(SSP.SSP_InitDevice(-1, 44100, 1000, 100, true));
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
}
