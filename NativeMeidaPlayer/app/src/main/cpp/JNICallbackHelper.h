//
// Created by dev on 2022/8/7.
//

#ifndef NATIVEMEIDAPLAYER_JNICALLBACKHELPER_H
#define NATIVEMEIDAPLAYER_JNICALLBACKHELPER_H

#include <jni.h>
#include "util.h"


class JNICallbackHelper {

private:
    JavaVM *vm = 0;
    JNIEnv *env = 0;
    // Java 层的对象 MediaPlayer.kt
    jobject job;
    // Java 层的方法 MediaPlayer#onPrepared()
    jmethodID jmd_prepared;
public:
    JNICallbackHelper(JavaVM *vm, JNIEnv *env, jobject job);

    ~JNICallbackHelper();

    void onPrepare(int threadMode);

};


#endif //NATIVEMEIDAPLAYER_JNICALLBACKHELPER_H
