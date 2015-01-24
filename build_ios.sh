#!/bin/bash

ROOT_BUILD_FOLDER="build"
LIB_NAME="libssp_player.a"
OUTPUT_FOLDER=output 
BUILD_CONFIG="Release"

# Create directory if does not exist
mkdir -p "${OUTPUT_FOLDER}"
rm -f "${OUTPUT_FOLDER}/${LIB_NAME}"

xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphoneos" clean BUILD_DIR="${ROOT_BUILD_FOLDER}"
xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphonesimulator" clean BUILD_DIR="${ROOT_BUILD_FOLDER}"

xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphoneos" build BUILD_DIR="${ROOT_BUILD_FOLDER}"
xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphonesimulator" build BUILD_DIR="${ROOT_BUILD_FOLDER}"

lipo -create "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}-iphoneos/${LIB_NAME}" "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}-iphonesimulator/${LIB_NAME}" -output "${LIB_NAME}"

rm -rf ${OUTPUT_FOLDER}/Includes
mkdir ${OUTPUT_FOLDER}/Includes
mv ${LIB_NAME} "${OUTPUT_FOLDER}/${LIB_NAME}"

if [ $? -eq 0 ]; then
    echo "Build successful."
    exit 0
else
    echo "Build FAILED!"
    exit 1
fi
