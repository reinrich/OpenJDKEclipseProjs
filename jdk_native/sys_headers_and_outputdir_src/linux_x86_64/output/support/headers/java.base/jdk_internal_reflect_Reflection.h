/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jdk_internal_reflect_Reflection */

#ifndef _Included_jdk_internal_reflect_Reflection
#define _Included_jdk_internal_reflect_Reflection
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jdk_internal_reflect_Reflection
 * Method:    getCallerClass
 * Signature: ()Ljava/lang/Class;
 */
JNIEXPORT jclass JNICALL Java_jdk_internal_reflect_Reflection_getCallerClass
  (JNIEnv *, jclass);

/*
 * Class:     jdk_internal_reflect_Reflection
 * Method:    getClassAccessFlags
 * Signature: (Ljava/lang/Class;)I
 */
JNIEXPORT jint JNICALL Java_jdk_internal_reflect_Reflection_getClassAccessFlags
  (JNIEnv *, jclass, jclass);

/*
 * Class:     jdk_internal_reflect_Reflection
 * Method:    areNestMates
 * Signature: (Ljava/lang/Class;Ljava/lang/Class;)Z
 */
JNIEXPORT jboolean JNICALL Java_jdk_internal_reflect_Reflection_areNestMates
  (JNIEnv *, jclass, jclass, jclass);

#ifdef __cplusplus
}
#endif
#endif
