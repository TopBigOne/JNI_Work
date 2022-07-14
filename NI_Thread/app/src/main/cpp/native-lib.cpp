#include <jni.h>
#include <string>


#include "native_log.h"
#include "normal_thread.h"



extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1thread_MainActivity_startNormalThread(JNIEnv *env, jobject thiz) {

 createThread();

}