#include <jni.h>
#include <string>

#include "include/test.h"
#include "BlockQueue.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_xzl_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ 123456 ";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_xzl_ndkdemo_MainActivity_intFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement intFromJNI()
    jint addnum = add(5, 6);
    test();
    return addnum;
}