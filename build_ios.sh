#!/bin/bash

ROOT_BUILD_FOLDER="build"
#LIB_NAME="libssp_player.a"
LIB_NAME="libplayer-ios-library.a"
#OUTPUT_FOLDER=RC.iOS.Binding.GoogleIMAVideoPlayer/GoogleIMAVideoPlayer
OUTPUT_FOLDER=output

BUILD_CONFIG="Release"

if [ $# -eq 1 ]; then
	if [[ $1 != "Debug" && $1 != "Release" ]]; then
        echo "Unknown build configuration provided"
        echo "Possible configurations : Release ou Debug. Default is Release"
        exit 1
	fi
    BUILD_CONFIG=$1
fi

echo "Cleaning the old lib ${OUTPUT_FOLDER}/${LIB_NAME}"
rm -f "${OUTPUT_FOLDER}/${LIB_NAME}"

echo ""
echo ""
echo ""
echo ""
echo ""
echo "--------------------------------------------------------"
echo "Will build using config ${BUILD_CONFIG}"
echo "--------------------------------------------------------"
echo ""
echo ""
echo ""
echo ""
echo ""


xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphoneos" clean BUILD_DIR="${ROOT_BUILD_FOLDER}"
xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphonesimulator" clean BUILD_DIR="${ROOT_BUILD_FOLDER}"

xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphoneos" build BUILD_DIR="${ROOT_BUILD_FOLDER}"
xcodebuild -scheme player-ios-library -configuration ${BUILD_CONFIG} -sdk "iphonesimulator" build BUILD_DIR="${ROOT_BUILD_FOLDER}"

lipo -create "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}-iphoneos/${LIB_NAME}" "${ROOT_BUILD_FOLDER}/${BUILD_CONFIG}-iphonesimulator/${LIB_NAME}" -output "${LIB_NAME}"

rm -rf ${OUTPUT_FOLDER}/Includes
mkdir ${OUTPUT_FOLDER}/Includes

find build -name "*.h" -type f -exec cp {} ./${OUTPUT_FOLDER}/Includes \;
rm -rf "${ROOT_BUILD_FOLDER}"

mv ${LIB_NAME} "${OUTPUT_FOLDER}/${LIB_NAME}"

echo ""
echo ""
echo ""
echo ""
echo ""

if [ $? -eq 0 ]; then
    echo "Library Build Success"
    exit 0
else
    echo "Library Build Failed"
    exit 1
fi
