LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE    := ffmpeg_wrapper
LOCAL_SRC_FILES := ffmpeg_wrapper.c
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ffmpeg
LOCAL_SRC_FILES := ffmpeg.c cmdutils.c ffmpeg_opt.c ffmpeg_filter.c
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := libavformat libavcodec libswscale libavutil libswresample libavfilter libavdevice
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libavcodec
LOCAL_SRC_FILES:= lib/libavcodec.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libavdevice
LOCAL_SRC_FILES:= lib/libavdevice.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libavformat
LOCAL_SRC_FILES:= lib/libavformat.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libswscale
LOCAL_SRC_FILES:= lib/libswscale.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libavutil
LOCAL_SRC_FILES:= lib/libavutil.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libavfilter
LOCAL_SRC_FILES:= lib/libavfilter.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= libswresample
LOCAL_SRC_FILES:= lib/libswresample.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)
