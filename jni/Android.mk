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
LOCAL_MODULE    := bassenc
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libbassenc.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -std=c99
LOCAL_MODULE    := libssp_player

VECTOR_FILES  := $(wildcard $(LOCAL_PATH)/../vector/*.c)
VECTOR_FILES  := $(VECTOR_FILES:$(LOCAL_PATH)/%=%)

PLAYER_FILES  := $(wildcard $(LOCAL_PATH)/../player/*.c)
PLAYER_FILES  := $(PLAYER_FILES:$(LOCAL_PATH)/%=%)

JNI_FILES  := $(wildcard $(LOCAL_PATH)/../jni/*.c)
JNI_FILES  := $(JNI_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(VECTOR_FILES)
LOCAL_SRC_FILES += $(PLAYER_FILES)
LOCAL_SRC_FILES += $(JNI_FILES)

LOCAL_SHARED_LIBRARIES := bass
LOCAL_SHARED_LIBRARIES += bass_fx
LOCAL_SHARED_LIBRARIES += bassmix
LOCAL_SHARED_LIBRARIES += bassenc

include $(BUILD_SHARED_LIBRARY)
