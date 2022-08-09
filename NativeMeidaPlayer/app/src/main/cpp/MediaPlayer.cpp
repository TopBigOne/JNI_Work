//
// Created by dev on 2022/8/7.
//

#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(const char *path, JNICallbackHelper *callbackHelper) {
    this->path = new char[strlen(path) + 1];
    strcpy(this->path, path);
    this->helper = callbackHelper;
}


void MediaPlayer::doOpenFile() {
    formatContext = avformat_alloc_context();
    AVDictionary *dictionary = nullptr;
    av_dict_set(&dictionary, "timeout", "5000000", 0);
    int result = avformat_open_input(&formatContext, this->path, nullptr, &dictionary);
    av_dict_free(&dictionary);
    if (result) {
        return;
    }

    result = avformat_find_stream_info(formatContext, nullptr);
    if (result < 0) {
        return;
    }
    for (int i = 0; i < formatContext->nb_streams; ++i) {
        AVStream *avStream = formatContext->streams[i];
        // 流中携带解码器参数
        AVCodecParameters *parameters = avStream->codecpar;
        // 流指定解码器
        AVCodec *codec = avcodec_find_decoder(parameters->codec_id);
        // 新建解码器上下文
        AVCodecContext *codecContext = avcodec_alloc_context3(codec);
        if (!codecContext) {
            return;
        }

        // 将流携带的解码器参数copy到解码器的上下文
        result = avcodec_parameters_to_context(codecContext, parameters);
        if (result < 0) {
            return;
        }
        // 打开解码器
        result = avcodec_open2(codecContext, codec, nullptr);
        if (result) {
            return;
        }
        if (parameters->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO) {
            this->audioChannel = new AudioChannel();
        } else if (parameters->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO) {
            this->videoChannel = new VideoChannel();
        }

    }// end for;
    if (this->audioChannel && this->videoChannel) {
        return;
    }
    helper->onPrepare(THREAD_CHILD);
}


void *task_open(void *args) {
    auto *player = static_cast<MediaPlayer *>(args);
    player->doOpenFile();
    return nullptr;
}

void MediaPlayer::openFile() {
    pthread_create(&pid_prepare, nullptr, task_open, this);
}

void MediaPlayer::start() {

}


MediaPlayer::~MediaPlayer() {
    if (path) {
        delete path;
    }
    if (helper) {
        delete helper;
    }
}