#include "node.h"
#include <jni.h>
#include <string>
#include <iostream>

#include "node_jni.h"

union charunion {
  char *chr;
  const char* cchr;
};


/**
 * TODO I can't decide on snake, camel case or C-style abbrev.
 */
namespace node
{
  /** I decided to pass a single concatenated jstring instead of an array of strings from java */
  JNIEXPORT jint JNICALL Java_NodeJNI_start(JNIEnv *env, jobject obj, jint jni_argc, jobjectArray jni_argv) {

    int len = env->GetArrayLength(jni_argv); // should be equal to argc

    const char** argv = new const char*[len];
    jstring* jstringArr = new jstring[len];

    // machine value type conversion, wow, gotta love high-level abstractions...
    for (int i=0; i<len; i++) {
        jstringArr[i] = (jstring) env->GetObjectArrayElement(jni_argv, i);
        argv[i] = env->GetStringUTFChars(jstringArr[i], 0);
    }

    // capture exit result
    int returnValue = node::Start((int) jni_argc, argv);
    // TODO jint is a typedef for long on an arm 64 and endianness? Phrack it. Just cast.
    // figure out macros later


    for (int i=0; i<len; i++) {
      // debug, TODO redirect stdout to android Log
      std::cout << std::string(argv[i]);

      // prevent memory leaks
      env->ReleaseStringUTFChars(jstringArr[i], argv[i]);
    }
    
    // deallocate arrays
    delete argv;
    delete jstringArr;

    return returnValue;
  }
}

