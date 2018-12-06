/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class java_util_zip_Deflater */

#ifndef _Included_java_util_zip_Deflater
#define _Included_java_util_zip_Deflater
#ifdef __cplusplus
extern "C" {
#endif
#undef java_util_zip_Deflater_DEFLATED
#define java_util_zip_Deflater_DEFLATED 8L
#undef java_util_zip_Deflater_NO_COMPRESSION
#define java_util_zip_Deflater_NO_COMPRESSION 0L
#undef java_util_zip_Deflater_BEST_SPEED
#define java_util_zip_Deflater_BEST_SPEED 1L
#undef java_util_zip_Deflater_BEST_COMPRESSION
#define java_util_zip_Deflater_BEST_COMPRESSION 9L
#undef java_util_zip_Deflater_DEFAULT_COMPRESSION
#define java_util_zip_Deflater_DEFAULT_COMPRESSION -1L
#undef java_util_zip_Deflater_FILTERED
#define java_util_zip_Deflater_FILTERED 1L
#undef java_util_zip_Deflater_HUFFMAN_ONLY
#define java_util_zip_Deflater_HUFFMAN_ONLY 2L
#undef java_util_zip_Deflater_DEFAULT_STRATEGY
#define java_util_zip_Deflater_DEFAULT_STRATEGY 0L
#undef java_util_zip_Deflater_NO_FLUSH
#define java_util_zip_Deflater_NO_FLUSH 0L
#undef java_util_zip_Deflater_SYNC_FLUSH
#define java_util_zip_Deflater_SYNC_FLUSH 2L
#undef java_util_zip_Deflater_FULL_FLUSH
#define java_util_zip_Deflater_FULL_FLUSH 3L
#undef java_util_zip_Deflater_FINISH
#define java_util_zip_Deflater_FINISH 4L
/*
 * Class:     java_util_zip_Deflater
 * Method:    init
 * Signature: (IIZ)J
 */
JNIEXPORT jlong JNICALL Java_java_util_zip_Deflater_init
  (JNIEnv *, jclass, jint, jint, jboolean);

/*
 * Class:     java_util_zip_Deflater
 * Method:    setDictionary
 * Signature: (J[BII)V
 */
JNIEXPORT void JNICALL Java_java_util_zip_Deflater_setDictionary
  (JNIEnv *, jclass, jlong, jbyteArray, jint, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    setDictionaryBuffer
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_java_util_zip_Deflater_setDictionaryBuffer
  (JNIEnv *, jclass, jlong, jlong, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    deflateBytesBytes
 * Signature: (J[BII[BIIII)J
 */
JNIEXPORT jlong JNICALL Java_java_util_zip_Deflater_deflateBytesBytes
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint, jbyteArray, jint, jint, jint, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    deflateBytesBuffer
 * Signature: (J[BIIJIII)J
 */
JNIEXPORT jlong JNICALL Java_java_util_zip_Deflater_deflateBytesBuffer
  (JNIEnv *, jobject, jlong, jbyteArray, jint, jint, jlong, jint, jint, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    deflateBufferBytes
 * Signature: (JJI[BIIII)J
 */
JNIEXPORT jlong JNICALL Java_java_util_zip_Deflater_deflateBufferBytes
  (JNIEnv *, jobject, jlong, jlong, jint, jbyteArray, jint, jint, jint, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    deflateBufferBuffer
 * Signature: (JJIJIII)J
 */
JNIEXPORT jlong JNICALL Java_java_util_zip_Deflater_deflateBufferBuffer
  (JNIEnv *, jobject, jlong, jlong, jint, jlong, jint, jint, jint);

/*
 * Class:     java_util_zip_Deflater
 * Method:    getAdler
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_java_util_zip_Deflater_getAdler
  (JNIEnv *, jclass, jlong);

/*
 * Class:     java_util_zip_Deflater
 * Method:    reset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_java_util_zip_Deflater_reset
  (JNIEnv *, jclass, jlong);

/*
 * Class:     java_util_zip_Deflater
 * Method:    end
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_java_util_zip_Deflater_end
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
