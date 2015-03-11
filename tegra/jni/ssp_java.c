#include "ssp_java.h"
#include "../player/ssp_public.h"

JNIEXPORT jint JNICALL Java_org_sessionsapp_player_SSP_SSP_1GetVersion
//JNIEXPORT jint JNICALL Java_org_sessionsapp_player_android_SSP_SSP_1GetVersion
//JNIEXPORT jint JNICALL Java_com_example_hellojni_SSP_SSP_1GetVersion
  (JNIEnv * je, jclass jc) {
  return SSP_GetVersion();
  }
  
JNIEXPORT jint JNICALL Java_org_sessionsapp_player_SSP_SSP_1Init
  (JNIEnv * je, jclass jc, jstring p0) {
	const char *str = (*je)->GetStringUTFChars(je, p0, 0);
	printf("%s", str);

  //return SSP_Init(p0);
	return SSP_Init(str);
  }
  
JNIEXPORT jint JNICALL Java_org_sessionsapp_player_SSP_SSP_1InitDevice
  (JNIEnv * je, jclass jc, jint p0, jint p1, jint p2, jint p3, jboolean p4) {
  return SSP_InitDevice(p0, p1, p2, p3, p4);
  }

JNIEXPORT jint JNICALL Java_org_sessionsapp_player_SSP_SSP_1FreeDevice
  (JNIEnv * je, jclass jc) {
  return SSP_FreeDevice();
  }
  
JNIEXPORT jint JNICALL Java_org_sessionsapp_player_SSP_SSP_1Free
  (JNIEnv * je, jclass jc) {
  return SSP_Free();
  }
