//
// Created by dev on 2022/8/7.
//

#include "JNICallbackHelper.h"

JNICallbackHelper::JNICallbackHelper(JavaVM *vm, JNIEnv *env, jobject job) {
    this->vm = vm;
    this->env = env;
    jclass mediaPlayerClass = env->GetObjectClass(job);
    jmd_prepared = env->GetMethodID(mediaPlayerClass, "onPrepared", "()V");
    this->job = env->NewGlobalRef(job);
}


void JNICallbackHelper::onPrepare(int threadMode) {
    if (threadMode == THREAD_MAIN) {
        // 主线程：直接使用持有的主线程 env
        env->CallVoidMethod(job, jmd_prepared);
        return;
    }
    if (threadMode == THREAD_CHILD) {
        JNIEnv *envChild;
        vm->AttachCurrentThread(&envChild, nullptr);
        envChild->CallVoidMethod(job, jmd_prepared);
        vm->DetachCurrentThread();
    }

}


JNICallbackHelper::~JNICallbackHelper() {
    vm = nullptr;
    env->DeleteGlobalRef(job);
    job = nullptr;
    env = nullptr;


}
