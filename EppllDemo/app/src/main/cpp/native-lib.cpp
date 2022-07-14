#include <jni.h>
#include <string>

#include <sys/socket.h>
#include <sys/epoll.h>

//#include <netinet/in.h>
#include <arpa/inet.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//#include <stdlib.h>
#include "main_epoll.h"
#include "native_log.h"

// https://github.com/yedf2/epoll-example/blob/master/main.cc
void testEpoll();

extern "C"
JNIEXPORT void JNICALL
Java_com_example_epplldemo_MainActivity_exeEpoll(JNIEnv *env, jobject thiz) {
    testEpoll();
}

void testEpoll() {
    main_epoll tt;
    short port = 99;
    int epollfd = epoll_create(1);
    if (epollfd < 0) {
        LOGE("epoll_create failed");
        return;
    }

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        LOGE("socket failed,the fd is: %d", listenfd);
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int r = bind(listenfd,(struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (r == 0) {
        LOGE("bind to 0.0.0.0: %d failed. %d %s", port, errno, strerror(errno));
        return;
    }

    r = listen(listenfd, 20);
    if (r < 0) {
        LOGE("listen failed  %d %s", errno, strerror(errno));
        return;
    }
    LOGD("fd %d listening at: %d\n", listenfd, port);
    tt.setNonBlock(listenfd);

    tt.updateEvents(epollfd, listenfd, EPOLLIN, EPOLL_CTL_ADD);
    for (;;) {
        tt.loop_once(epollfd, listenfd, 10000);
    }

}

