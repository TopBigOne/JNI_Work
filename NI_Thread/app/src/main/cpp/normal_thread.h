//
// Created by dev on 2022/7/14.
//

#include <pthread.h>
#include "native_log.h"

#ifndef JNI_THREAD_NORMAL_THREAD_H
#define JNI_THREAD_NORMAL_THREAD_H



void createThread();
void *threadDoThing(void *data);

#endif //JNI_THREAD_NORMAL_THREAD_H
