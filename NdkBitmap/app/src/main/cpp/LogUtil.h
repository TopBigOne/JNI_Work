//
// Created by dev on 2022/8/9.
//

#ifndef NDKBITMAP_LOGUTIL_H
#define NDKBITMAP_LOGUTIL_H

#ifdef __ANDROID__
#include <android/log.h>
#endif

const char *TAG = "xiao_ya_native";

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))


#endif //NDKBITMAP_LOGUTIL_H
