#!/usr/bin/env bash

./build_native.sh
ant debug
cd bin
adb uninstall org.cocos2dx.hellolua
adb install HelloLua-debug.apk
cd ..
adb logcat
