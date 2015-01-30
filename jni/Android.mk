# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := bass
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libbass.so
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../ffmpeg/libs/arm-linux-androideabi4.7_1/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := bass_fx
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libbass_fx.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := bassmix
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libbassmix.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -std=c99
LOCAL_MODULE    := libssp_player
LOCAL_SRC_FILES := ../player/ssp_bass.c
LOCAL_SRC_FILES := ../player/ssp_convertaudio.c
LOCAL_SRC_FILES := ../player/ssp_device.c
LOCAL_SRC_FILES := ../player/ssp_eqpreset.c
LOCAL_SRC_FILES := ../player/ssp_loop.c
LOCAL_SRC_FILES := ../player/ssp_marker.c
LOCAL_SRC_FILES := ../player/ssp_mixer.c
LOCAL_SRC_FILES := ../player/ssp_player_playback.c
LOCAL_SRC_FILES := ../player/ssp_player_seeking.c
LOCAL_SRC_FILES := ../player/ssp_player.c
LOCAL_SRC_FILES := ../player/ssp_playerchannels.c
LOCAL_SRC_FILES := ../player/ssp_playerplugins.c
LOCAL_SRC_FILES := ../player/ssp_playhead.c
LOCAL_SRC_FILES := ../player/ssp_playlist.c
LOCAL_SRC_FILES := ../player/ssp_public.c
LOCAL_SRC_FILES := ../vector/vector.c
LOCAL_SHARED_LIBRARIES := bass, bass_fx, bassmix
include $(BUILD_SHARED_LIBRARY)
