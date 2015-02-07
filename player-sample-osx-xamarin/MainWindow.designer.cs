// WARNING
//
// This file has been generated automatically by Xamarin Studio to store outlets and
// actions made in the UI designer. If it is removed, they will be lost.
// Manual changes to this file may not be handled correctly.
//
using MonoMac.Foundation;
using System.CodeDom.Compiler;

namespace playersampleosxxamarin
{
	[Register ("MainWindowController")]
	partial class MainWindowController
	{
		[Outlet]
		MonoMac.AppKit.NSTextField lblFilePath { get; set; }

		[Outlet]
		MonoMac.AppKit.NSTextField lblPlaylist { get; set; }

		[Outlet]
		MonoMac.AppKit.NSTextField lblPosition { get; set; }

		[Outlet]
		MonoMac.AppKit.NSTextField lblState { get; set; }

		[Outlet]
		MonoMac.AppKit.NSTextField lblVersion { get; set; }

		[Action ("actionClose:")]
		partial void actionClose (MonoMac.Foundation.NSObject sender);

		[Action ("actionNext:")]
		partial void actionNext (MonoMac.Foundation.NSObject sender);

		[Action ("actionOpenAudioFiles:")]
		partial void actionOpenAudioFiles (MonoMac.Foundation.NSObject sender);

		[Action ("actionPause:")]
		partial void actionPause (MonoMac.Foundation.NSObject sender);

		[Action ("actionPlay:")]
		partial void actionPlay (MonoMac.Foundation.NSObject sender);

		[Action ("actionPrevious:")]
		partial void actionPrevious (MonoMac.Foundation.NSObject sender);

		[Action ("actionStop:")]
		partial void actionStop (MonoMac.Foundation.NSObject sender);
		
		void ReleaseDesignerOutlets ()
		{
			if (lblVersion != null) {
				lblVersion.Dispose ();
				lblVersion = null;
			}

			if (lblState != null) {
				lblState.Dispose ();
				lblState = null;
			}

			if (lblPlaylist != null) {
				lblPlaylist.Dispose ();
				lblPlaylist = null;
			}

			if (lblFilePath != null) {
				lblFilePath.Dispose ();
				lblFilePath = null;
			}

			if (lblPosition != null) {
				lblPosition.Dispose ();
				lblPosition = null;
			}
		}
	}

	[Register ("MainWindow")]
	partial class MainWindow
	{
		
		void ReleaseDesignerOutlets ()
		{
		}
	}
}
