#include <jni.h>
/* Header for class NodeJNI */
#ifndef _Included_NodeJNI
#define _Included_NodeJNI
namespace node {
  /*
   * Class: NodeJNI
   * Method: start
   * TODO Figure out signature later
   * TODO Figure out namespace?
   */
  JNIEXPORT jint JNICALL Java_NodeJNI_start(JNIEnv *env, jobject obj, jint argc, jobjectArray argv);
}
#endif
