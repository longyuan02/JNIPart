package com.example.jni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        PrintAction jni = new PrintAction();
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(jni.inputString("我来到,我看到,我征服"));

        int[] get = jni.getArrayList(new int[]{10, 12, 13, 14, 15, 16, 17, 18, 19, 20});
        for (int i = 0; i < 10; i++) {
            Log.e("返回数据值======:", get[i] + ".");
        }
        jni.callMethod();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public void showToast() {
        Toast.makeText(this, "被调用了", Toast.LENGTH_LONG).show();
    }
}
