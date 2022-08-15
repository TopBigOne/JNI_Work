#include <jni.h>
#include <string>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include "android/log.h"

#define TAG "xiao_ya"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);

void testCpu() {
    int cpus = 0;
    int i = 0;
    cpu_set_t mask;
    cpu_set_t get;

    cpus = sysconf(_SC_NPROCESSORS_CONF);

    LOGD("cpus: %d\n", cpus);

    CPU_ZERO(&mask);    /* 初始化set集，将set置为空*/
    CPU_SET(0, &mask);  /* 依次将0、1、2、3号cpu加入到集合，前提是你的机器是多核处理器*/
    CPU_SET(1, &mask);
    CPU_SET(2, &mask);
    CPU_SET(3, &mask);

    //void CPU_CLR (int cpu, cpu_set_t *set) //这个宏将 指定的 cpu 从 CPU 集 set 中删除
    //int CPU_ISSET (int cpu, const cpu_set_t *set) //如果 cpu 是 CPU 集 set 的一员，这个宏就返回一个非零值（true），否则就返回零（false）

    /*设置cpu 亲和性（affinity）*/

    /*sched_setaffinity函数设置进程为pid的这个进程,让它运行在mask所设定的CPU上.如果pid的值为0,
     *则表示指定的是当前进程,使当前进程运行在mask所设定的那些CPU上.
     *第二个参数cpusetsize是mask所指定的数的长度.通常设定为sizeof(cpu_set_t).
     *如果当前pid所指定的进程此时没有运行在mask所指定的任意一个CPU上,
     *则该指定的进程会从其它CPU上迁移到mask的指定的一个CPU上运行.*/
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        LOGE("Set CPU affinity failure, ERROR:%s\n", strerror(-1));
        return;
    }
    usleep(1000); /* 让当前的设置有足够时间生效*/

    /*查看当前进程的cpu 亲和性*/
    CPU_ZERO(&get);
    /*sched_getaffinity函数获得pid所指示的进程的CPU位掩码,并将该掩码返回到mask所指向的结构中.
 　　*即获得指定pid当前可以运行在哪些CPU上.
　　 *同样,如果pid的值为0.也表示的是当前进程*/
    if (sched_getaffinity(0, sizeof(get), &get) == -1) {
        LOGE("get CPU affinity failue, ERROR:%s\n", strerror(-1));
        return;
    }

    /*查看当前进程的在哪个cpu核上运行*/
    for (i = 0; i < cpus; i++) {
        if (CPU_ISSET(i, &get)) { /*查看cpu i 是否在get 集合当中*/
            LOGD("this process %d of running processor: %d\n", getpid(), i);
        }
    }
    sleep(6); //让程序停在这儿，方便top命令查看
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_jar_testcpu_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    const char *tempChar = "hello 筱雅";
    testCpu();
    return env->NewStringUTF(tempChar);

}