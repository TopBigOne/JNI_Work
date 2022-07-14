//
// Created by dev on 2022/7/11.
//

#include "main_epoll.h"
#include "native_log.h"
void main_epoll::setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        LOGE("fcntl failed");

    }
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (flags < 0) {
        LOGE("fcntl failed %d", flags);
    }
}

void main_epoll::updateEvents(int efd, int fd, int events, int op) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    LOGD("%s fd %d events read %d write %d\n",
         op == EPOLL_CTL_MOD ? "mod" : "add", fd, ev.events & EPOLLIN, ev.events & EPOLLOUT);

    int r = epoll_ctl(efd, op, fd, &ev);
    if (r < 0) {
        LOGE("epoll_ctl failed");
    }

}

void main_epoll::handleAccept(int efd, int fd) {
    struct sockaddr_in raddr;
    socklen_t rsz = sizeof(raddr);
    int cfd = accept(fd, (struct sockaddr *) &raddr, &rsz);
    if (cfd < 0) {
        LOGE("accept failed");
    }
    sockaddr_in peer, local;
    socklen_t alen = sizeof(peer);
    int r = getpeername(cfd, (sockaddr *) &peer, &alen);
    if (r < 0) {
        LOGE("getpeername failed");
    }
    printf("accept a connection from %s\n", inet_ntoa(raddr.sin_addr));
    setNonBlock(cfd);
    updateEvents(efd, cfd, EPOLLIN | EPOLLOUT, EPOLL_CTL_ADD);
}

void main_epoll::handleRead(int efd, int fd) {
    char buf[4096];
    int n = 0;
    while ((n = ::read(fd, buf, sizeof buf)) > 0) {
        printf("read %d bytes\n", n);
        LOGE("read %d bytes\n", n);
        //写出读取的数据
        int r = ::write(fd, buf, n);
        //实际应用中，写出数据可能会返回EAGAIN，此时应当监听可写事件，当可写时再把数据写出
        if (r <= 0) {
            LOGE("write error");
        }
    }
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        return;
    }

    //实际应用中，n<0应当检查各类错误，如EINTR
    if (n < 0) {
        LOGE("read error");
    }
    printf("fd %d closed\n", fd);
    close(fd);
}

void main_epoll::handleWrite(int efd, int fd) {
    //实际应用应当实现可写时写出数据，无数据可写才关闭可写事件
    updateEvents(efd, fd, EPOLLIN, EPOLL_CTL_MOD);
}

void main_epoll::loop_once(int efd, int lfd, int waitms) {
    const int kMaxEvents = 20;
    struct epoll_event activeEvs[100];
    int n = epoll_wait(efd, activeEvs, kMaxEvents, waitms);

    LOGI("epoll_wait return %d\n", n);
    for (int i = 0; i < n; i++) {
        int fd = activeEvs[i].data.fd;
        int events = activeEvs[i].events;
        if (events & (EPOLLIN | EPOLLERR)) {
            if (fd == lfd) {
                handleAccept(efd, fd);
            } else {
                handleRead(efd, fd);
            }
        } else if (events & EPOLLOUT) {
            handleWrite(efd, fd);
        } else {
            LOGE("unknown event");
        }
    }
}
