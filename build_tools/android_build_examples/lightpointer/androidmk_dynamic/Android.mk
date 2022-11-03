LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lightpointer-mk-dynamic
LOCAL_SRC_FILES := lightpointer.cpp
LOCAL_SHARED_LIBRARIES := \
        libcutils \
        libutils

include $(BUILD_EXECUTABLE)
