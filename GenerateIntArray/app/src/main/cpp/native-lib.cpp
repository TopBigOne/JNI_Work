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
    // 访问静态成员变量
    jfieldID sFieldId = env->GetStaticFieldID(clz, "sName", "Ljava/lang/String;");
    if (sFieldId) {
        auto jStr = static_cast<jstring>(env->GetStaticObjectField(clz, sFieldId));
        // 将 jstring 转换为 C 风格字符串
        const char *sStr = env->GetStringUTFChars(jStr, JNI_FALSE);
        // 释放资源
        env->ReleaseStringUTFChars(jStr, sStr);
        jstring newString = env->NewStringUTF("修改静态成员变量");
        if (newString) {
            env->SetStaticObjectField(clz, sFieldId, newString);
        }

    }


}