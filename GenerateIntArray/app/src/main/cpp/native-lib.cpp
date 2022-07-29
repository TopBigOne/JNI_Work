#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_jar_generateintarray_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_jar_generateintarray_MainActivity_createIntArray(JNIEnv *env, jobject thiz, jint size) {
    jintArray jarr = env->NewIntArray(size);
    jint *carr = env->GetIntArrayElements(jarr, JNI_FALSE);
    for (int i = 0; i < size; ++i) {
        carr[i] = i;
    }
    env->ReleaseIntArrayElements(jarr, carr, JNI_FALSE);
    return jarr;
}