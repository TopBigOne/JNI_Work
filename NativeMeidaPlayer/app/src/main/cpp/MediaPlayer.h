//
// Created by dev on 2022/8/7.
//

#ifndef NATIVEMEIDAPLAYER_MEDIAPLAYER_H
#define NATIVEMEIDAPLAYER_MEDIAPLAYER_H

#include <jni.h>
#include "util.h"
#include <cstring>
#include <pthread.h>
#include "VideoChannel.h"
#include "AudioChannel.h"
#include "JNICallbackHelper.h"

extern "C" {
#include "libavformat/avformat.h"
};

class MediaPlayer {
private:
    char *path = 0;
    JNICallbackHelper *helper = 0;
    pthread_t pid_prepare = 0;
    AVFormatContext *formatContext = 0;
    AudioChannel *audioChannel = 0;
    VideoChannel *videoChannel = 0;

public:
    MediaPlayer(const char *path, JNICallbackHelper *callbackHelper);

    ~MediaPlayer();

    void openFile();

    void doOpenFile();

    void start();

};


#endif //NATIVEMEIDAPLAYER_MEDIAPLAYER_H
