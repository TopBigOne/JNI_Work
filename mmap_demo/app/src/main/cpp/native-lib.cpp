#include <jni.h>
#include <string>

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include "native_log.h"

// https://juejin.cn/post/7119116943256190990
int execMmap();


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mmap_1demo_MainActivity_testMMAp(
        JNIEnv *env,
        jobject /* this */) {

    execMmap();


    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


int execMmap() {
    pid_t c_pid = fork();
    char *shm = (char *) mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,
                              0);
    if (c_pid == -1) {
        LOGE("fork failed....");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {
        LOGI("The parent process pid is %d\n", getpid());
        sprintf(shm, "%s", "hello, my child");
        LOGD("Parent process got a message: %s\n", shm);
        wait(nullptr);
    } else {
        LOGI("The child process pid: %d\n", getpid());
        sprintf(shm, "%s", "hello, father");
        LOGD("Child process got a message: %s\n", shm);
      //  exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;

}