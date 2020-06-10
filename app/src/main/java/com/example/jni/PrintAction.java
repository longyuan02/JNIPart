package com.example.jni;

import android.app.Activity;
import android.util.Log;
import android.widget.Toast;

import java.sql.Array;
import java.util.ArrayList;

public class PrintAction {
    static {
        System.loadLibrary("fnative-lib");
    }

    public native String stringFromJNI();

    public native String getString();

    public native String inputString(String str);

    //获取数组
    public native int[] getArrayList(int[] list);

    public native void callMethod();

    public void showToast() {
        Log.e("调用输出======","printAction");
    }

}
