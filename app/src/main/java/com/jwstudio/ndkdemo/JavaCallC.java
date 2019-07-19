package com.jwstudio.ndkdemo;

public class JavaCallC {

    // 让c代码做加法运算，把结果返回
    public native int add(int x, int y);

    // 从Java传入字符，c代码进行拼接
    public native String stringConcatenation(String s);

    // 让c代码给每个元素都加上10
    public native int[] increaseArrayElements(int[] intArry);

    // 静态方法
    public static native String greeting();

    // 通过C++来打日志
    public native void myLog();

}
