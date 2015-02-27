#!/bin/bash

echo "Building libssp_player..."
ndk-build clean
ndk-build

echo "Copying libs to sample application directories..."
rsync --recursive libs/* player-sample-android/app/src/main/jniLibs
rsync --recursive libs/* player-sample-android-xamarin/lib

echo "All done."