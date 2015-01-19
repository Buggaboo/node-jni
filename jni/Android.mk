LOCAL_PATH:= $(call my-dir)

# TODO symlink from node workspace to  $(LOCALPATH)/node
# TODO adapt Android.mk to reflect new path

include $(CLEAR_VARS)

LOCAL_MODULE    := node
LOCAL_CFLAGS    := -Werror

LOCAL_CPP_EXTENSION := .cc .cpp .cxx

# TODO blog/complain that everything else other than LOCAL_SRC_FILES
# is relative to $ANDROID_NDK
LOCAL_EXPORT_C_INCLUDES += \
    $(LOCAL_PATH)/../src \
    $(LOCAL_PATH)/../deps/v8/include \
    $(LOCAL_PATH)/../android-toolchain/include \
    $(LOCAL_PATH)/../android-toolchain/sysroot/usr/include \
    $(LOCAL_PATH)/../android-toolchain/lib/gcc/arm-linux-androideabi/4.8/include \
    $(LOCAL_PATH)/../deps/uv/include \
    $(LOCAL_PATH)/../deps/cares/include \
    $(LOCAL_PATH)/../deps/openssl/openssl/include

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../src \
    $(LOCAL_PATH)/../deps/v8/include \
    $(LOCAL_PATH)/../android-toolchain/include \
    $(LOCAL_PATH)/../android-toolchain/sysroot/usr/include \
    $(LOCAL_PATH)/../android-toolchain/lib/gcc/arm-linux-androideabi/4.8/include \
    $(LOCAL_PATH)/../deps/uv/include \
    $(LOCAL_PATH)/../deps/cares/include \
    $(LOCAL_PATH)/../deps/openssl/openssl/include

LOCAL_STATIC_LIBRARIES += \
    $(LOCAL_PATH)/../out/Release/libv8_base.arm.a \
    $(LOCAL_PATH)/../out/Release/libv8_nosnapshot.arm.a \
    $(LOCAL_PATH)/../out/Release/libnode.a \
    $(LOCAL_PATH)/../out/Release/libuv.a \
    $(LOCAL_PATH)/../out/Release/libopenssl.a \
    $(LOCAL_PATH)/../out/Release/libchrome_zlib.a \
    $(LOCAL_PATH)/../out/Release/libcares.a

LOCAL_SRC_FILES := ../src/node_jni.cc

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true # it compiles, but solves nothing

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)
