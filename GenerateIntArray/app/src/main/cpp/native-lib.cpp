#include <jni.h>
#include <string>


#include <android/log.h>

const char *TAG = "xiao_ya";

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))


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
/**
 * 利用 jobjectArray 创建java 层String 类型的数组；
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_jar_generateintarray_MainActivity_createStringArray(JNIEnv *env, jobject thiz, jint size) {
    jclass jStringClazz = env->FindClass("java/lang/String");
    jstring initialStr = env->NewStringUTF("09090");
    jobjectArray jarr = env->NewObjectArray(size, jStringClazz, initialStr);
    for (int i = 0; i < size; ++i) {
        char str[10];
        sprintf(str, "%s", "陈筱雅");
        jstring jStr = env->NewStringUTF(str);
        env->SetObjectArrayElement(jarr, i, jStr);
    }
    return jarr;
}
/**
 * 修改java层的成员变量： 普通变量和静态成员变量
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_generateintarray_MainActivity_accessJavaField(JNIEnv *env, jobject thiz) {
    jclass clz = env->GetObjectClass(thiz);
    // 访问成员变量
    jfieldID mFieldId = env->GetFieldID(clz, "mName", "Ljava/lang/String;");
    if (mFieldId) {
        auto jStr = static_cast<jstring>(env->GetObjectField(thiz, mFieldId));
        // 将 jstring 转换为 C 风格字符串
        const char *sStr = env->GetStringUTFChars(jStr, JNI_FALSE);
        LOGD("java 层的原始 mName：%s", sStr);
        // 释放资源
        env->ReleaseStringUTFChars(static_cast<jstring>(jStr), sStr);

        jstring newString = env->NewStringUTF("修成员变量:666");
        if (newString) {
            env->SetObjectField(thiz, mFieldId, newString);
        }

    }


}
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_generateintarray_MainActivity_accessJavaStaticField(JNIEnv *env, jobject thiz) {
    jclass clz = env->GetObjectClass(thiz);
    // 访问静态成员变量
    jfieldID sFieldId = env->GetStaticFieldID(clz, "sName", "Ljava/lang/String;");
    if (sFieldId) {

        jstring jStr = static_cast<jstring>(env->GetStaticObjectField(clz, sFieldId));
        // 将 jstring 转换为 C 风格字符串
        const char *sStr = env->GetStringUTFChars(jStr, JNI_FALSE);
        LOGD("java 层的原始 sName：%s", sStr);
        // 释放资源
        env->ReleaseStringUTFChars(jStr, sStr);

        jstring newString = env->NewStringUTF("修成员变量:555");
        if (newString) {
            env->SetStaticObjectField(clz, sFieldId, newString);
        }

    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_generateintarray_MainActivity_invokeStaticJavaMethod(JNIEnv *env, jobject thiz) {
    jclass mainClass = env->GetObjectClass(thiz);
    jmethodID helloOneId = env->GetStaticMethodID(mainClass, "helloOne", "(Ljava/lang/String;)V");
    jstring pone = env->NewStringUTF("中午好好吃饭");
    env->CallStaticVoidMethod(mainClass, helloOneId, pone);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jar_generateintarray_MainActivity_invokeNormalJavaMethod(JNIEnv *env, jobject thiz) {
    // 获取ArrayList 的 class 路径
    jclass arrayListConstructClass = env->FindClass("java/util/ArrayList");
    // 获取ArrayList构造函数id
    jmethodID arrayListConstruct = env->GetMethodID(arrayListConstructClass, "<init>", "(I)V");
    // capacity;
    jint size = 100;
    // 创建
    jobject arrayList = env->NewObject(arrayListConstructClass, arrayListConstruct, size);
    // 获取ArrayList 的add() 函数id
    jmethodID addId = env->GetMethodID(arrayListConstructClass, "add", "(Ljava/lang/Object;)Z");
    for (int i = 0; i < 10; ++i) {
        jstring tempStr = env->NewStringUTF("筱");
        env->CallBooleanMethod(arrayList, addId, tempStr);
    }

    jclass mainClass = env->GetObjectClass(thiz);
    jmethodID helloTwoId = env->GetMethodID(mainClass, "helloTwo",
                                            "(Ljava/util/ArrayList;)V");
    env->CallVoidMethod(thiz, helloTwoId, arrayList);


}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    LOGE("JNI_OnLoad---->");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {

    LOGE("JNI_OnUnload---->");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jar_generateintarray_MainActivity_throwExceptionByNative(JNIEnv *env, jobject thiz) {
    jclass exceptionClz = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(exceptionClz, "这是一个来自native的Exception");
    jthrowable exeThrowable = env->ExceptionOccurred();
    if (exeThrowable) {
        LOGE("native 出现了一个Exception");

    }
    env->ExceptionClear();
}