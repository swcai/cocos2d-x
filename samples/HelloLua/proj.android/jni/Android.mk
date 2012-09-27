LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libhellolua

LOCAL_MODULE_FILENAME := libhellolua

LOCAL_SRC_FILES := hellolua/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../../../scripting/lua/cocos2dx_support/CCLuaEngine.cpp \
                   ../../../../scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
                   ../../../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp \
                   ../../../../scripting/lua/cocos2dx_support/tolua_fix.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../../../scripting/lua/luafilesystem/src \
		    $(LOCAL_PATH)/../../../../scripting/lua/socket/src 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += liblfs_static
LOCAL_WHOLE_STATIC_LIBRARIES += libluamime_static
LOCAL_WHOLE_STATIC_LIBRARIES += libluasocket_static

# LOCAL_LDLIBS := -ldl
# LOCAL_SHARED_LIBRARIE := libdl

include $(BUILD_SHARED_LIBRARY)

BASE_PATH := $(LOCAL_PATH)
#include $(BASE_PATH)/../../../../scripting/lua/socket/Android.mk
#include $(BASE_PATH)/../../../../scripting/lua/luafilesystem/Android.mk

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android/jni)
$(call import-module,scripting/lua/socket)
$(call import-module,scripting/lua/luafilesystem)
