LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := libluasocket

LOCAL_MODULE_FILENAME := libsocketcore

LOCAL_SRC_FILES := src/auxiliar.c \
	    src/buffer.c \
	    src/except.c \
	    src/inet.c \
	    src/io.c \
	    src/luasocket.c \
	    src/options.c \
	    src/select.c \
	    src/tcp.c \
	    src/timeout.c \
	    src/udp.c \
	    src/unix.c \
	    src/usocket.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lua \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support 
          
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
                    $(LOCAL_PATH)/../lua 

#LOCAL_SHARED_LIBRARIES := libhellolua
LOCAL_CFLAGS := -fPIC
LOCAL_LDLIBS := -lhellolua -L$(LOCAL_PATH)/../../../samples/HelloLua/proj.android/libs/armeabi/

#LOCAL_CFLAGS += -fvisibility=hidden
#LOCAL_CFLAGS += -fPIC

#LOCAL_LDLIBS := -lhellolua
#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libluamime

LOCAL_MODULE_FILENAME := libmimecore

LOCAL_SRC_FILES := src/mime.c
         
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lua \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support 
          
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
                    $(LOCAL_PATH)/../lua 

#LOCAL_SHARED_LIBRARIES := libhellolua
LOCAL_CFLAGS := -fPIC
LOCAL_LDLIBS := -lhellolua -L$(LOCAL_PATH)/../../../samples/HelloLua/proj.android/libs/armeabi/
#LOCAL_LDLIBS := -lhellolua

#LOCAL_CFLAGS += -fvisibility=hidden
#LOCAL_CFLAGS += -fPIC

include $(BUILD_SHARED_LIBRARY)
