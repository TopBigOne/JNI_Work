#include <jni.h>
#include <string>


#include "native_log.h"
#include "normal_thread.h"
#include "pthread.h"
#include "unistd.h"
#include "queue"
#include "WlListener.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1thread_MainActivity_startNormalThread(JNIEnv *env, jobject thiz) {

    createThread();

}

//2、-------------------------------线程锁------------------------------------------

std::queue<int> queue; //产品队列，里面是int的队列
pthread_t pthread_produc; //生产者线程
pthread_t pthread_customer; //消费者线程
pthread_mutex_t mutex; //线程锁
pthread_cond_t cond; //条件对象


void *startProduct(void *) {
    while (queue.size() < 50) {
        LOGD("生产者生产一个产品");
        //操作队列前先加锁
        pthread_mutex_lock(&mutex);
        queue.push(1);
        if (!queue.empty()) {
            LOGD("生产者通知消费者有产品产生，产品数量为：%d", queue.size());
            pthread_cond_signal(&cond); //有了产品通知消费者
        }
        pthread_mutex_unlock(&mutex); //解锁线程
        sleep(4); //休息4秒，单位是秒
    }
    pthread_exit(&pthread_produc);
}

[[noreturn]] void *startCustomer(void *data) {
    char *prod = (char *) data;
    LOGD("startCustomer : %s", prod);

    while (true) //这里用死循环，时间情况应该给一个变量来控制跳出循环
    {
        pthread_mutex_lock(&mutex); //操作队列前先加锁
        if (!queue.empty()) {
            queue.pop();
            LOGE("消费者消费一个产品，产品数量为：%d", queue.size());
        } else {
            LOGE("产品消费完了，等待生产者生产......");
            pthread_cond_wait(&cond, &mutex); //阻塞线程等待生产者的通知
        }
        pthread_mutex_unlock(&mutex);//解锁线程
        usleep(500 * 1000); //休息0.5秒，usleep单位是微妙
    }
    pthread_exit(&pthread_customer);
}

void initMutex() {
    pthread_mutex_init(&mutex, nullptr); //初始化锁对象 对应pthread_mutex_destroy销毁锁对象
    pthread_cond_init(&cond, nullptr); //初始化条件变量 对应pthread_cond_destroy销毁条件变量
    pthread_create(&pthread_produc, nullptr, startProduct, nullptr); //创建生产者线程，并传递参数
    pthread_create(&pthread_customer, nullptr, startCustomer, nullptr); //创建消费者线程
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1thread_MainActivity_startMutexThread(JNIEnv *env, jobject thiz) {
    //初始化时，先往队列中添加10个产品
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }
    initMutex();
}


JavaVM *jvm;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}

pthread_t callbackThread;

void *callBackT(void *data) {
    //获取WlListener指针
    auto *wlListener = (WlListener *) data;
    wlListener->onError(1, 200, " Child thread running success");
    pthread_exit(&callbackThread);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1thread_MainActivity_starPThreadCallback(JNIEnv *env, jobject thiz) {
    auto *wlListener = new WlListener(jvm, env, env->NewGlobalRef(thiz));
    //在主线程中调用java方法
    wlListener->onError(0, 100, "JNIENV thread running success!");
    //开启子线程，并把WlListener指针传递到子线程中
    pthread_create(&callbackThread, nullptr, callBackT, wlListener);
}