LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := luasocket_static

LOCAL_MODULE_FILENAME := libluasocket

LOCAL_SRC_FILES := src/auxiliar.c \
	    src/buffer.c \
	    src/except.c \
	    src/inet.c \
	    src/io.c \
	    src/luasocket.c \
	    src/mime.c \
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

include $(BUILD_STATIC_LIBRARY)
