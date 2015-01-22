#include "node.h"
#include <jni.h>
#include <string.h>
//#include <iostream>

#include "node_jni.h"

using namespace node;

/**
 * Ol' dirty trick to convert const char* to char*
 */
union charunion {
  char *chr;
  const char* cchr;
};

using namespace node;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_nl_sison_android_nodejni_NodeJNI_start
  (JNIEnv *, jclass, jint, jobjectArray)

    int len = env->GetArrayLength(jni_argv); // should be equal to argc

    char** argv = new char*[len];
    jstring* jstringArr = new jstring[len];

    // type conversion, wow
    for (int i=0; i<len; i++) {
        jstringArr[i] = (jstring) env->GetObjectArrayElement(jni_argv, i);
        charunion char_union;
        char_union.cchr = env->GetStringUTFChars(jstringArr[i], 0);
        argv[i] = char_union.chr;
    }

    // capture exit result
    int returnValue = node::Start(len /*(int) jni_argc*/, argv);
    // TODO jint is a typedef for long on an arm 64 and how about endianness? Phrack it. Just cast.
    // figure out with macros later


    for (int i=0; i<len; i++) {
        // debug, TODO redirect stdout to android Log
//      std::cout << std::string(argv[i]); // stdout is /dev/null on Android

        // prevent memory leaks
        env->ReleaseStringUTFChars(jstringArr[i], argv[i]);
    }
    
    // deallocate arrays
    delete argv;
    delete jstringArr;

    return returnValue;
}

#ifdef __cplusplus
}
#endif
