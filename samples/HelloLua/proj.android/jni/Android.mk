LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellolua_shared

LOCAL_MODULE_FILENAME := libhellolua

LOCAL_SRC_FILES := hellolua/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../../../scripting/lua/cocos2dx_support/CCLuaEngine.cpp \
                   ../../../../scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
                   ../../../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp \
                   ../../../../scripting/lua/cocos2dx_support/tolua_fix.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/../../../../scripting/lua/socket/Android.mk

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android/jni)


