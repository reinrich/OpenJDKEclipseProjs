/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class java_net_Inet4AddressImpl */

#ifndef _Included_java_net_Inet4AddressImpl
#define _Included_java_net_Inet4AddressImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     java_net_Inet4AddressImpl
 * Method:    getLocalHostName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_java_net_Inet4AddressImpl_getLocalHostName
  (JNIEnv *, jobject);

/*
 * Class:     java_net_Inet4AddressImpl
 * Method:    lookupAllHostAddr
 * Signature: (Ljava/lang/String;)[Ljava/net/InetAddress;
 */
JNIEXPORT jobjectArray JNICALL Java_java_net_Inet4AddressImpl_lookupAllHostAddr
  (JNIEnv *, jobject, jstring);

/*
 * Class:     java_net_Inet4AddressImpl
 * Method:    getHostByAddr
 * Signature: ([B)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_java_net_Inet4AddressImpl_getHostByAddr
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     java_net_Inet4AddressImpl
 * Method:    isReachable0
 * Signature: ([BI[BI)Z
 */
JNIEXPORT jboolean JNICALL Java_java_net_Inet4AddressImpl_isReachable0
  (JNIEnv *, jobject, jbyteArray, jint, jbyteArray, jint);

#ifdef __cplusplus
}
#endif
#endif
