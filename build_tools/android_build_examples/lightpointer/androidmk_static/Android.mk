LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lightpointer-mk-static
LOCAL_SRC_FILES := lightpointer.cpp
LOCAL_STATIC_LIBRARIES := \
        libcutils \
        libutils
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_STATIC_EXECUTABLE)
