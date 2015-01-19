# lifesaver: https://aabdelfattah.wordpress.com/2013/04/08/android-build-system-ultimate-guide/
APP_STL := gnustl_static # c++_static # stlport_static...
APP_PLATFORM := android-9
APP_ABI := armeabi armeabi-v7a # TODO all (soon also: x86, arm64)
#NDK_TOOLCHAIN_VERSION := 4.8
NDK_TOOLCHAIN := armeabi-4.8
