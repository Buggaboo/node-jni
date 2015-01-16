# Broken, WIP
# Biggest obstacle, how the **** am I supposed to import all the header files dynamically???
## source: http://kvurd.com/blog/compiling-a-cpp-library-for-android-with-android-studio/

LOCAL_PATH := $(call my-dir)

# static library info
LOCAL_MODULE := libnode
LOCAL_SRC_FILES := libcares \
  libchrome_zlib \
  libhttp_parser \
  libnode \
  libopenssl \
  libuv \
  libv8_base.arm \
  libv8_nosnapshot.arm \
  ../../../../../src-cpp/node_jni.cc

LOCAL_EXPORT_C_INCLUDES := ../../../../../src-cpp/node_jni.h
include $(PREBUILT_STATIC_LIBRARY)

# wrapper info
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += ../prebuild/include
LOCAL_MODULE    := your-wrapper
LOCAL_SRC_FILES := your-wrapper.cpp
LOCAL_STATIC_LIBRARIES := libYourLibrary
include $(BUILD_SHARED_LIBRARY)
