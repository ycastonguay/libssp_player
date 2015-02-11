// WARNING
//
// This file has been generated automatically by Xamarin Studio from the outlets and
// actions declared in your storyboard file.
// Manual changes to this file will not be maintained.
//
using System;
using Foundation;
using UIKit;
using System.CodeDom.Compiler;

namespace playersampleiosxamarin
{
	[Register ("PlayerViewController")]
	partial class PlayerViewController
	{
		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UIButton buttonNext { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UIButton buttonPause { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UIButton buttonPlay { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UIButton buttonPrevious { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UIButton buttonStop { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UILabel lblFilePath { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UILabel lblPlaylist { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UILabel lblPosition { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UILabel lblState { get; set; }

		[Outlet]
		[GeneratedCode ("iOS Designer", "1.0")]
		UILabel lblVersion { get; set; }

		[Action ("buttonNext_TouchUpInside:")]
		[GeneratedCode ("iOS Designer", "1.0")]
		partial void buttonNext_TouchUpInside (UIButton sender);

		[Action ("buttonPause_TouchUpInside:")]
		[GeneratedCode ("iOS Designer", "1.0")]
		partial void buttonPause_TouchUpInside (UIButton sender);

		[Action ("buttonPlay_TouchUpInside:")]
		[GeneratedCode ("iOS Designer", "1.0")]
		partial void buttonPlay_TouchUpInside (UIButton sender);

		[Action ("buttonPrevious_TouchUpInside:")]
		[GeneratedCode ("iOS Designer", "1.0")]
		partial void buttonPrevious_TouchUpInside (UIButton sender);

		[Action ("buttonStop_TouchUpInside:")]
		[GeneratedCode ("iOS Designer", "1.0")]
		partial void buttonStop_TouchUpInside (UIButton sender);

		void ReleaseDesignerOutlets ()
		{
			if (buttonNext != null) {
				buttonNext.Dispose ();
				buttonNext = null;
			}
			if (buttonPause != null) {
				buttonPause.Dispose ();
				buttonPause = null;
			}
			if (buttonPlay != null) {
				buttonPlay.Dispose ();
				buttonPlay = null;
			}
			if (buttonPrevious != null) {
				buttonPrevious.Dispose ();
				buttonPrevious = null;
			}
			if (buttonStop != null) {
				buttonStop.Dispose ();
				buttonStop = null;
			}
			if (lblFilePath != null) {
				lblFilePath.Dispose ();
				lblFilePath = null;
			}
			if (lblPlaylist != null) {
				lblPlaylist.Dispose ();
				lblPlaylist = null;
			}
			if (lblPosition != null) {
				lblPosition.Dispose ();
				lblPosition = null;
			}
			if (lblState != null) {
				lblState.Dispose ();
				lblState = null;
			}
			if (lblVersion != null) {
				lblVersion.Dispose ();
				lblVersion = null;
			}
		}
	}
}
