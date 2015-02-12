libssp_player (Sessions Player)
====

This library is an audio player written in C for [Sessions](http://mp4m.org), a music player for musicians.

The source code is released under the GPLv3 license. For more information on the Sessions license, go to http://www.mp4m.org/license.

How to build libssp_player
--

iOS
-

Requirements:
+ Xcode 6+

Run the following script to build a universal static library (ARMv7, ARM64 and i386):

`./build_ios.sh`

The static library `libssp_player.a` will be found in the `output` folder.

OSX
-

Requirements:
+ Xcode 6+

Run the following script to build a dynamic library for 32-bit and 64-bit:

`./build_osx.sh`

The dynamic library `libssp_player.dylib` will be found in the `output` folder.

Android
-

Requirements:
+ Android NDK

Run the standard NDK build command to build a dynamic library for ARMEABI, ARMEABI-V7A and X86:

`ndk-build`

The dynamic libraries for each platform will be found in the `libs` folder.

Windows
-

Requirements:
+ Visual Studio

Use Visual Studio to open the Visual C++ project found in the root folder: 

`libssp_player.sln`

Linux
-

Requirements:
+ GCC

Run the standard make command to build a dynamic library on the current architecture (32-bit/64-bit):

`make`

Unit Tests
--
Unit tests are using the [Check](http://check.sourceforge.net/) framework and are written in C.

The unit test runner can be found in [`player-test`](player-test) and the test cases in [`tests`](tests).

Samples
--

There are samples for just about every platform and language available:
+  __iOS__ / Objective-C: [`player-sample-ios`](player-sample-ios)
+  __iOS__ / Xamarin: [`player-sample-ios-xamarin`](player-sample-ios-xamarin)
+  __OSX__ / Objective-C: [`player-sample-osx`](player-sample-osx)
+  __OSX__ / Xamarin: [`player-sample-osx-xamarin`](player-sample-osx-xamarin)
+  __Android__ / Java: [`player-sample-android`](player-sample-android)
+  __Android__ / Xamarin: [`player-sample-android-xamarin`](player-sample-android-xamarin)
+  __Linux__ / QT: [`player-sample-linux-qt`](player-sample-linux-qt)
+  __Linux__ / Gtk-sharp: [`player-sample-linux-gtk-sharp`](player-sample-linux-gtk-sharp)
+  __Windows__ / WPF: [`player-sample-win32-wpf`](player-sample-win32-wpf)
+  __Console__ / C: [`player-sample-console`](player-sample-console)
