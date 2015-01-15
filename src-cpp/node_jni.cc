#include "node.h"
#include <jni.h>

#include "node_jni.h"

namespace node
{
  /** I decided to pass a single concatenated jstring instead of an array of strings from java */
  JNIEXPORT jint JNICALL Java_NodeJNI_start(JNIEnv *env, jobject obj, jint argc, jobjectArray argv) {

    int stringCount = env->GetArrayLength(stringArray);

    for (int i=0; i<stringCount; i++) {
        jstring string = (jstring) GetObjectArrayElement(env, stringArray, i);
        const char *rawString = GetStringUTFChars(env, string, 0);
        // Don't forget to call `ReleaseStringUTFChars` when you're done.
    }

    const jbyte *str;
    str = (*env)->GetStringUTFChars(env, argv, str);

    // capture exit result
    int returnValue = node::Start((int) argc, argv);

    // prevent memory leaks
    for (int i=0; i<stringCount; i++) {
      (*env)->ReleaseStringUTFChars(env, argv, str);
    }


    return returnValue;
  }
}

