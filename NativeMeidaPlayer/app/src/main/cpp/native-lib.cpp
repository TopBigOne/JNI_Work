#include <jni.h>
#include <string>

#include "MediaPlayer.h"

#define TAG "xiao_ya"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);


// libsubc 是 C 语言实现的，需要转为 C 语言的编译方式
extern "C" {
#include "ffmpeg/include/libavutil/avutil.h"
#include "ffmpeg/include/libavformat/avformat.h" // 打开封装格式文件 .mp4 .flv .xxx ...
#include "ffmpeg/include/libavcodec/avcodec.h" // 音频 视频 编码 解码 工作 codec编解码库
}
JavaVM *vm = nullptr;

jint JNI_OnLoad(JavaVM *vm, void *args) {
    ::vm = vm;
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jar_nativemeidaplayer_MediaPlayer_stopNative(JNIEnv *env, jobject thiz, jlong ptr) {


}
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_nativemeidaplayer_MediaPlayer_startNative(JNIEnv *env, jobject thiz, jlong ptr) {
    auto *player = reinterpret_cast<MediaPlayer * >(ptr);
    player->start();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_nativemeidaplayer_MediaPlayer_releaseNative(JNIEnv *env, jobject thiz, jlong ptr) {

}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_jar_nativemeidaplayer_MediaPlayer_prepareNative(JNIEnv *env, jobject thiz,
                                                         jstring video_path) {
    const char *path = env->GetStringUTFChars(video_path, JNI_FALSE);

    auto *helper = new JNICallbackHelper(vm, env, thiz);
    auto *player = new MediaPlayer(path, helper);
    player->openFile();
    // 返回一个播放器指针
    return reinterpret_cast<jlong>(player);
}