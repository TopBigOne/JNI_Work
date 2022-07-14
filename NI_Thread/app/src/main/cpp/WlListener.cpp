//
// Created by dev on 2022/7/14.
//

#include "WlListener.h"
#include "native_log.h"

WlListener::WlListener(JavaVM *vm, _JNIEnv *env, jobject obj) {
    jvm = vm;
    jenv = env;
    jobj = obj;
    jclass clz = env->GetObjectClass(jobj);
    if (!clz) {
        LOGE("get jclass wrong");
        return;
    }

    jmid = env->GetMethodID(clz, "onError", "(ILjava/lang/String;)V");
//    if (!jmid) {
//        LOGE("get jmethodID wrong");
//        return;
//    }
}

/**
 *
 * @param type  0：env线程 1：子线程
 * @param code
 * @param msg
 */
void WlListener::onError(int type, int code, const char *msg) {
    if (type == 0) {
        LOGD("main thread");
        jstring jmsg = jenv->NewStringUTF(msg);
        jenv->CallVoidMethod(jobj, jmid, code, jmsg);
        jenv->DeleteLocalRef(jmsg);
        return;
    }
    if (type == 1) {
        LOGD("p thread thread");
        JNIEnv *env;
        jvm->AttachCurrentThread(&env, nullptr);

        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj, jmid, code, jmsg);
        env->DeleteLocalRef(jmsg);

        jvm->DetachCurrentThread();
    }
}
