//
// Created by dev on 2022/7/11.
//

#ifndef EPPLLDEMO_MAIN_EPOLL_H
#define EPPLLDEMO_MAIN_EPOLL_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


class main_epoll {

public:

    void setNonBlock(int fd);

    void updateEvents(int efd, int fd, int events, int op);

    void handleAccept(int efd, int fd);

    void handleRead(int efd, int fd);

    void handleWrite(int efd, int fd);

    void loop_once(int efd, int lfd, int waitms);

};


#endif //EPPLLDEMO_MAIN_EPOLL_H
