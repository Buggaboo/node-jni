#include <jni.h>

#include "node.h"
/* Header for class NodeJNI */
#ifndef _Included_NodeJNI
#define _Included_NodeJNI

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class: NodeJNI
 * Method: start
 * TODO Figure out signature later
 * TODO Figure out namespace?
 */
JNIEXPORT jint JNICALL Java_NodeJNI_start(JNIEnv *env, jobject obj, jint argc, jobjectArray argv);

#ifdef __cplusplus
}
#endif
#endif
