//
// Created by dev on 2022/7/11.
//

#ifndef TESTBOOSTCMAKE_NATIVE_LOG_H
#define TESTBOOSTCMAKE_NATIVE_LOG_H

#include <android/log.h>

#define LOG_ENABLE

#define LOG_TAG "native_ya"

#ifdef LOG_ENABLE

#undef LOG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#define LOGF(...)
#endif


#endif //TESTBOOSTCMAKE_NATIVE_LOG_H
