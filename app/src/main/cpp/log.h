//
// Created by sqwu on 2020/4/9.
//

#ifndef TENSORFLOWDEMO_LOG_H
#define TENSORFLOWDEMO_LOG_H


//#define ANDROID_NDK false

//#if ANDROID_NDK
#include <jni.h>
#include <android/log.h>
//#endif

// ----------------------------------------------------------

const int VERBOSE = 1;
const int DEBUG = 2;
const int INFO = 3;
const int WARN = 4;
const int ERROR = 5;
const int NOTHING = 6;

const int LEVEL = VERBOSE;

// ----------------------------------------------------------

//void log_print_verbose(const char *TAG, const char *fmt, ...);
//void log_print_debug(const char *TAG, const char *fmt, ...);
//void log_print_info(const char *TAG, const char *fmt, ...);
//void log_print_warn(const char *TAG, const char *fmt, ...);
//void log_print_error(const char *TAG, const char *fmt, ...);

//#if ANDROID_NDK
#define LOGV(TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
//#else
//#define LOGV(TAG, fmt, ...) log_print_verbose(TAG, fmt, ##__VA_ARGS__)
//#define LOGD(TAG, fmt, ...) log_print_debug(TAG, fmt, ##__VA_ARGS__)
//#define LOGI(TAG, fmt, ...) log_print_info(TAG, fmt, ##__VA_ARGS__)
//#define LOGW(TAG, fmt, ...) log_print_warn(TAG, fmt, ##__VA_ARGS__)
//#define LOGE(TAG, fmt, ...) log_print_error(TAG, fmt, ##__VA_ARGS__)
//#endif
#endif //TENSORFLOWDEMO_LOG_H
