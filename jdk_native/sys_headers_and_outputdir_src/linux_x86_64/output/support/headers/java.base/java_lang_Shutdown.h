/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class java_lang_Shutdown */

#ifndef _Included_java_lang_Shutdown
#define _Included_java_lang_Shutdown
#ifdef __cplusplus
extern "C" {
#endif
#undef java_lang_Shutdown_MAX_SYSTEM_HOOKS
#define java_lang_Shutdown_MAX_SYSTEM_HOOKS 10L
/*
 * Class:     java_lang_Shutdown
 * Method:    beforeHalt
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_java_lang_Shutdown_beforeHalt
  (JNIEnv *, jclass);

/*
 * Class:     java_lang_Shutdown
 * Method:    halt0
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_java_lang_Shutdown_halt0
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
