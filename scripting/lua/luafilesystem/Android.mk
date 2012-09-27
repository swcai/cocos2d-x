LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := liblfs_static

LOCAL_MODULE_FILENAME := liblfs

LOCAL_SRC_FILES := src/lfs.c
          
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lua \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support 
          
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
                    $(LOCAL_PATH)/../lua 

# LOCAL_SHARED_LIBRARIES := libhellolua

#LOCAL_CFLAGS := -fPIC
#LOCAL_LDLIBS := -lhellolua -L$(LOCAL_PATH)/../../../samples/HelloLua/proj.android/libs/armeabi/
# LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_STATIC_LIBRARY)
