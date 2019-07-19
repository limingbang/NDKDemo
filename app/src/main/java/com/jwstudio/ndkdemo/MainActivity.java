package com.jwstudio.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    // 固定写法，加载动态库，要在调用本地方法之前调用，可以写在其它类里
    static {
        // 库的名称是native-lib
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JavaCallC javaCallC = new JavaCallC();
        CCallJava cCallJava = new CCallJava();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());

        // Java调用C++
//        tv.setText(javaCallC.add(10,50) + "");

//        tv.setText(javaCallC.stringConcatenation("I am java"));

        /*int[] a = {1, 2, 3, 4, 5, 6};
        int[] b = javaCallC.increaseArrayElements(a);
        for (int i = 0; i < b.length; i++) {
            Log.d("TAG", b[i] + "");
        }*/

//        tv.setText(javaCallC.greeting());

        // C++调用Java

//        cCallJava.callbackAdd();

//        cCallJava.callbackHelloFromJava();

//        cCallJava.callbackPrintString();

//        cCallJava.callbackSayHello();

        // 打印日志
        javaCallC.myLog();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    // 本地方法的声明方式，该方法的主体实现在cpp目录下的native-lib.cpp，
    // 而且是用C/C++来实现的
    // 该方法的目的是从C/C++哪里得到一个字符串
    public native String stringFromJNI();
}
