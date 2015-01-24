#!/bin/bash

ROOT_BUILD_FOLDER="build"
LIB_NAME="libssp_player.dylib"
OUTPUT_FOLDER=output
BUILD_CONFIG="Release"

# Create directory if does not exist
mkdir -p "${OUTPUT_FOLDER}"
rm -f "${OUTPUT_FOLDER}/${LIB_NAME}"
rm -rf "${OUTPUT_FOLDER}/include"

xcodebuild -scheme player-osx-library -configuration ${BUILD_CONFIG} clean BUILD_DIR="${ROOT_BUILD_FOLDER}"
xcodebuild -scheme player-osx-library -configuration ${BUILD_CONFIG} build BUILD_DIR="${ROOT_BUILD_FOLDER}"

mv "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}/${LIB_NAME}" "${OUTPUT_FOLDER}/${LIB_NAME}"
mv "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}/usr/local/include" "${OUTPUT_FOLDER}"

if [ $? -eq 0 ]; then
    echo "Build successful."
    exit 0
else
    echo "Build FAILED!"
    exit 1
fi
