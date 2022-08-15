//
// Created by dev on 2022/7/12.
//

#ifndef MMAP_DEMO_NATIVE_LOG_H
#define MMAP_DEMO_NATIVE_LOG_H

#include <android/log.h>

const char *TAG = "xiao_ya";
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))


#endif //MMAP_DEMO_NATIVE_LOG_H
