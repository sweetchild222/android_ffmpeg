#include <jni.h>

//#include "libavformat/avformat.h"
//#include "ffmpeg.h"

#include <stdlib.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define LOG_TAG "ffmpeg"

#define LOGI(...) __android_log_print(4, LOG_TAG, __VA_ARGS__);

static jboolean logEnable = JNI_FALSE;
static int progress = 0;


static void log_callback(void *ptr, int level, const char *fmt, va_list va)
{

    if(logEnable == JNI_TRUE)
	    __android_log_vprint(4, LOG_TAG, fmt, va);

    const int bufferSize = 256;
    char buffer[bufferSize];

    vsnprintf(buffer, bufferSize, fmt, va);

    const char *dstTag = ", dts ";

    char *result = strstr(buffer, dstTag);

    if(result != 0) {

        result += strlen(dstTag);
        int isProgressLine = 1;

        for(int i = 0; (strlen(result) - 1) > i; i++) {
            if(result[i] < 0x30 || result[i] > 0x39) {
                isProgressLine = 0;
                break;
            }
        }

        if(isProgressLine == 1)
            progress = atoi(result);
    }
}


JNIEXPORT jint JNICALL Java_com_skt_ffmpeg_ndk_progress(JNIEnv *env, jobject object)
{
    return progress;
}


JNIEXPORT jint JNICALL Java_com_skt_ffmpeg_ndk_merge(JNIEnv *env, jobject object, jstring videoPath, jstring bgmPath, jstring micPath, jstring outPath, jboolean log)
{
    const char* nativeVideoPath = (*env)->GetStringUTFChars( env, videoPath , NULL);
    const char* nativeBGMPath = (*env)->GetStringUTFChars( env, bgmPath, NULL);
    const char* nativeMICPath = (*env)->GetStringUTFChars( env, micPath, NULL);
    const char* nativeOutput = (*env)->GetStringUTFChars( env, outPath, NULL);

    void* handle = dlopen("libffmpeg.so", RTLD_NOW);

    jint result = -1;

    if(handle){

        progress = 0;

        int *(*ffmpeg)(int argc, char **argv, void(*callback)(void *, int, const char *, va_list)) = dlsym(handle, "ffmpeg");

        if(ffmpeg != 0)  {

             const int argc = 14;
             logEnable = log;

             char *argv[argc] = {"ffmpeg", "-i", nativeVideoPath, "-i", nativeBGMPath, "-i", nativeMICPath, "-filter_complex", "amerge", "-ac", "2", "-vcodec", "copy",  nativeOutput};
             result = ffmpeg(argc, argv, log_callback);
        }

        dlclose(handle);
    }

    (*env)->ReleaseStringUTFChars(env, videoPath, nativeVideoPath);
    (*env)->ReleaseStringUTFChars(env, bgmPath, nativeBGMPath);
    (*env)->ReleaseStringUTFChars(env, micPath, nativeMICPath);
    (*env)->ReleaseStringUTFChars(env, micPath, nativeOutput);

    return result;
}
