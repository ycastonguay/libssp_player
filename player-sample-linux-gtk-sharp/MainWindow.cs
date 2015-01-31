using System;
using Gtk;
using org.sessionsapp.player;

public partial class MainWindow: Gtk.Window
{
	public MainWindow() : base (Gtk.WindowType.Toplevel)
	{
		//Build ();
		SSP.SSP_Init();
	}

	protected void OnDeleteEvent (object sender, DeleteEventArgs a)
	{
		Application.Quit ();
		a.RetVal = true;
	}
}
