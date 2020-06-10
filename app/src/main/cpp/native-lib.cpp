#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "BT"
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__) // 定义LOGD类型
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)  // 定义LOGI类型
#define LOGW(...)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)  // 定义LOGW类型
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__) // 定义LOGE类型
#define LOGF(...)__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__) // 定义LOGF类

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jni_PrintAction_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_PrintAction_getString(JNIEnv *env, jobject thiz) {
    std::string name = "JNIName";
    int a = 10;
    std::to_string(a);//int 转string
    float time_use = 0;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start,
                 NULL); //gettimeofday(&start,&tz);结果一样
    printf("start.tv_sec:%d\n", start.tv_sec);
    printf("start.tv_usec:%d\n", start.tv_usec);
    int i = 100;
    while (i--);
    gettimeofday(&end, NULL);
    return env->NewStringUTF(std::to_string(a).c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_PrintAction_showString(JNIEnv *env, jobject thisz) {
//        javaString =(*env).NewStringUTF(env,"Hellow")
    jstring hello = env->NewStringUTF("Hello from C++");
    return hello;
}

/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char *JString2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env).FindClass("java/lang/String");
//    jstring strencode = (*env).NewStringUTF("GB2312");
    jstring strencode = (*env).NewStringUTF("UTF-8");
    jmethodID mid = (*env).GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env).CallObjectMethod(jstr, mid,
                                                           strencode); // String .getByte("GB2312");
    jsize alen = (*env).GetArrayLength(barr);
    jbyte *ba = (*env).GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env).ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_PrintAction_inputString(JNIEnv *env, jobject thiz, jstring str) {
    jboolean *isCopy;
    char *hello11 = "C++";
    char *forUser = JString2CStr(env, str);
//    const char *schar = env->GetStringUTFChars(str, NULL);

    return env->NewStringUTF(strcat(forUser, hello11));
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_jni_PrintAction_getArrayList(JNIEnv *env, jobject thiz, jintArray list) {
    //获取数组长度
    jint length = (*env).GetArrayLength(list);
    //对直接指针操作 获取java传入值
    jint *arrayPointer = (*env).GetIntArrayElements(list, NULL);
    //建议写法把int i放在循环体外,在循环体内可能到时有的平台编译错误
    jint i;
    for (i = 0; i < length; i++) {
        *(arrayPointer + i) += 20;
    }
    //副本操作:将修改完的jint值赋值给jintArray数组
    (*env).SetIntArrayRegion(list, 0, length, arrayPointer);
    LOGE("数组长度======:%d", length);
    //释放资源,防止内存泄露
    (*env).ReleaseIntArrayElements(list, arrayPointer, 0);
    return list;
}
/*
    //原生代码可以创建Java应用程序使用的直接字节缓冲区,该过程提供C原生字节数组为基础
    unsigned char *buffer = (unsigned char *) malloc(1024);
    jobject directBuffer;
    directBuffer = env->NewDirectByteBuffer(buffer, 1024);
    unsigned char *getbuffer;
    //获取原生字节数组地址
    getbuffer = (unsigned char *) env->GetDirectBufferAddress(directBuffer);
*/

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_PrintAction_callMethod(JNIEnv *env, jobject thiz) {
    jclass clazz;
    char *className = "com/example/jni/PrintAction";
    clazz = (*env).FindClass(className);
    jfieldID instanceFieldId;
    jmethodID instanceMethod;
    const char *functionName1 = "showToast";
    const char *type1 = "()V";
    instanceMethod = (*env).GetMethodID(clazz, functionName1, type1);
    env->CallVoidMethod(thiz, instanceMethod);
}