# libssp_player (Sessions Player)

This library is an audio player written in C for [Sessions](http://mp4m.org), a music player for musicians.

The source code is released under the GPLv3 license. For more information on the Sessions license, go to http://www.mp4m.org/license.

Sessions uses the __BASS audio library__, which is a commercial library, but available for free for open source projects. The Sessions source code repository contains the BASS static/dynamic libraries needed to build each platform. To download updated versions of the BASS library, go to the [BASS library home page](http://www.un4seen.com). Please note that newer versions might introduce breaking changes.

## How to build libssp_player

### iOS

Use __Xcode__ to run the following script and build a universal static library for ARMv7, ARM64 and i386:

`./build_ios.sh`

The static library `libssp_player.a` will be found in the `output` folder.

### OSX

Use __Xcode__ to run the following script and build a dynamic library for 32-bit and 64-bit:

`./build_osx.sh`

The dynamic library `libssp_player.dylib` will be found in the `output` folder.

### Android

Use the __Android NDK__ to build a dynamic library for ARMEABI, ARMEABI-V7A and X86:

`ndk-build`

The dynamic libraries for each platform will be found in the `libs` folder.

### Windows

Use __Visual Studio__ to open the Visual C++ project found in the root folder: 

`libssp_player.sln`

### Linux

Run the standard `make` command with __GCC__ installed to build a dynamic library on the current architecture (32-bit or 64-bit).

## Unit Tests

Unit tests are using the [Check](http://check.sourceforge.net/) framework and are written in C.

The unit test runner can be found in [`player-test`](player-test) and the test cases in [`tests`](tests).

## Samples

There are samples for just about every platform and language available:
+  __iOS__ / Objective-C: [`player-sample-ios`](player-sample-ios)
+  __iOS__ / Xamarin: [`player-sample-ios-xamarin`](player-sample-ios-xamarin)
+  __OSX__ / Objective-C: [`player-sample-osx`](player-sample-osx)
+  __OSX__ / Xamarin: [`player-sample-osx-xamarin`](player-sample-osx-xamarin)
+  __Android__ / Java: [`player-sample-android`](player-sample-android)
+  __Android__ / Xamarin: [`player-sample-android-xamarin`](player-sample-android-xamarin)
+  __Linux__ / QT: [`player-sample-linux-qt`](player-sample-linux-qt)
+  __Linux__ / GTK#: [`player-sample-linux-gtk-sharp`](player-sample-linux-gtk-sharp)
+  __Windows__ / MFC: [`player-sample-win32-mfc`](player-sample-win32-mfc)
+  __Windows__ / WPF: [`player-sample-win32-wpf`](player-sample-win32-wpf)
+  __Console__ / C: [`player-sample-console`](player-sample-console)

*'Sessions' and 'MPfm: Music Player for Musicians' are © 2011-2015 Yanick Castonguay and is released under the GPLv3 license.*
*The BASS audio library is © 1999-2015 Un4seen Developments.*
