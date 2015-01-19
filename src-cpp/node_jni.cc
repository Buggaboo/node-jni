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

/**
 * TODO I can't decide on snake, camel case or C-style abbrev.
 */
/** I decided to pass a single concatenated jstring instead of an array of strings from java */
JNIEXPORT jint JNICALL Java_NodeJNI_start(JNIEnv *env, jobject obj, jint jni_argc, jobjectArray jni_argv) {

    int len = env->GetArrayLength(jni_argv); // should be equal to argc

    char** argv = new char*[len];
    jstring* jstringArr = new jstring[len];

    // machine value type conversion, wow, gotta love high-level abstractions...
    for (int i=0; i<len; i++) {
        jstringArr[i] = (jstring) env->GetObjectArrayElement(jni_argv, i);
        charunion char_union;
        char_union.cchr = env->GetStringUTFChars(jstringArr[i], 0);
        argv[i] = char_union.chr;
    }

    // capture exit result
    int returnValue = node::Start(len /*(int) jni_argc*/, argv);
    // TODO jint is a typedef for long on an arm 64 and endianness? Phrack it. Just cast.
    // figure out macros later


    for (int i=0; i<len; i++) {
        // debug, TODO redirect stdout to android Log
//      std::cout << std::string(argv[i]);

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
