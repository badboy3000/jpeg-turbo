LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := jpeg


LOCAL_LDLIBS    := -ljnigraphics -llog
LOCAL_SRC_FILES := \
	JpgEncoder.cpp \
	jpeg.cpp \

LOCAL_STATIC_LIBRARIES := \
	libjpeg-turbo \
	
include $(BUILD_SHARED_LIBRARY)

#include $(BUILD_EXECUTABLE)
