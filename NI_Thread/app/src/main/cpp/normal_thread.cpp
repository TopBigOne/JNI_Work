//
// Created by dev on 2022/7/14.
//

#include "normal_thread.h"

//  线程对象
pthread_t pthread;

void createThread() {

    pthread_t  tid =  pthread_create(&pthread, nullptr, threadDoThing, nullptr);
    LOGD("normal thread : %ld",tid);
}

void *threadDoThing(void *data) {
    LOGD(" pthread do sth....");
    pthread_exit(&pthread);
}