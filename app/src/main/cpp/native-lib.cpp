// jni.h这个头文件必须要导进来
#include <jni.h>
#include <string>

#include <android/log.h>
// 定义Log的tag
#define LOG_TAG "System.out"
// 不同等级的Log
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// 你可以使用C++实现本地方法。然而，那样你必须将实现本地方法的函数声明为extern"C"
// （这可以阻止C++编译器混编方法名）
// 方法命名的格式：
// JNIEXPORT 返回类型 JNICALL Java_+方法的全类名（.用_替代）
extern "C" JNIEXPORT jstring JNICALL
Java_com_jwstudio_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    // 标准模板库（STL）提供了一个std::string类
    std::string hello = "Hello from C++";
    // c_str()，一个将string转换为 const* char的函数
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jwstudio_ndkdemo_JavaCallC_add(JNIEnv *env, jobject instance, jint x, jint y) {
    int result = x + y;
    return result;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_jwstudio_ndkdemo_JavaCallC_increaseArrayElements(JNIEnv *env, jobject instance,
                                                          jintArray intArry_) {
    jint *intArry = env->GetIntArrayElements(intArry_, NULL); // 访问数组元素
    jsize len = env->GetArrayLength(intArry_); // 数组长度

    // 遍历数组，给每个元素加10
    for (int i = 0; i < len; ++i) {
        *(intArry + i) += 10;
    }

    env->ReleaseIntArrayElements(intArry_, intArry, 0);

    return intArry_; // 注意这里返回的是intArry_，而不是intArry，原因在于指针
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jwstudio_ndkdemo_JavaCallC_stringConcatenation(JNIEnv *env, jobject instance, jstring s_) {
    const char *s = env->GetStringUTFChars(s_, 0); // 得到java传递的string，固定写法

    // 使用C语言的方式来拼接字符串
    char *fromC = ",I am C++.";
    int len = strlen(s) + strlen(fromC);
    char returnValue[len];
    strcpy(returnValue, s); // 把s复制到returnValue
    strcat(returnValue, fromC); // 把fromC所指向的字符串追加到returnValue所指向的字符串的结尾

    // 虚拟机必须知道你何时使用完字符串，这样它就能进行垃圾回收（垃圾回收器是在一个独立线程中运行的，它能够中
    // 断本地方法的执行），基于这个原因，你必须调用ReleaseStringUTFChars函数
    env->ReleaseStringUTFChars(s_, s);

    return env->NewStringUTF(returnValue); // 生成字符串并返回
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jwstudio_ndkdemo_JavaCallC_greeting(JNIEnv *env, jclass type) { // 注意第二个参数
    std::string returnValue = "Hello,I am static method.";

    return env->NewStringUTF(returnValue.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jwstudio_ndkdemo_CCallJava_callbackAdd(JNIEnv *env, jobject instance) {

    // 得到字节码,使用/代替.
    jclass jclazz = env->FindClass("com/jwstudio/ndkdemo/CCallJava");

    // 得到方法,最后一个参数的方法签名
    jmethodID jmethodIDs = env->GetMethodID(jclazz, "add", "(II)I");

    // 实例化该类
    jobject jobject1 = env->AllocObject(jclazz);

    // 调用方法，方法的返回值是int
    jint value = env->CallIntMethod(jobject1, jmethodIDs, 99, 1);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jwstudio_ndkdemo_CCallJava_callbackHelloFromJava(JNIEnv *env, jobject instance) {

    // 得到字节码,使用/代替.
    jclass jclazz = env->FindClass("com/jwstudio/ndkdemo/CCallJava");

    // 得到方法,最后一个参数的方法签名
    jmethodID jmethodIDs = env->GetMethodID(jclazz, "helloFromJava", "()V");

    // 实例化该类
    jobject jobject1 = env->AllocObject(jclazz);

    // 调用方法，方法的返回值是void
    env->CallVoidMethod(jobject1, jmethodIDs);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jwstudio_ndkdemo_CCallJava_callbackPrintString(JNIEnv *env, jobject instance) {

    // 得到字节码,使用/代替.
    jclass jclazz = env->FindClass("com/jwstudio/ndkdemo/CCallJava");

    // 得到方法,最后一个参数的方法签名
    jmethodID jmethodIDs = env->GetMethodID(jclazz, "printString", "(Ljava/lang/String;)V");

    // 实例化该类
    jobject jobject1 = env->AllocObject(jclazz);

    // 调用方法
    jstring jst = env->NewStringUTF("I am afu!!!(*env)->");
    // 方法的返回值是void
    env->CallVoidMethod(jobject1, jmethodIDs, jst);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jwstudio_ndkdemo_CCallJava_callbackSayHello(JNIEnv *env, jobject instance) {

    // 得到字节码,使用/代替.
    jclass jclazz = env->FindClass("com/jwstudio/ndkdemo/CCallJava");

    // 得到方法,最后一个参数的方法签名
    jmethodID jmethodIDs = env->GetStaticMethodID(jclazz, "sayHello", "(Ljava/lang/String;)V");

    // 实例化该类
    jstring jst = env->NewStringUTF("I am 123456android");
    // 注意这个调用的是static方法
    env->CallStaticVoidMethod(jclazz, jmethodIDs, jst);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jwstudio_ndkdemo_JavaCallC_myLog(JNIEnv *env, jobject instance) {

    // 打印不同等级的log
    LOGD("result=%s", "result1");
    LOGI("result=%s", "result2");
    LOGE("result=%s", "result2");

}