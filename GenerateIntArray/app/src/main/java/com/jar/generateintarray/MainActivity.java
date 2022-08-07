package com.jar.generateintarray;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import android.os.Bundle;

import com.jar.generateintarray.databinding.ActivityMainBinding;

import java.util.Arrays;

/**
 * 原文：https://mp.weixin.qq.com/s/i45NAQetqq-dcMxQqGI5yQ
 */
public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("generateintarray");
    }

    private ActivityMainBinding binding;
    private static String sName = "静态---》筱雅";
    private String mName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        // Example of a call to a native method
        setEvent(binding.btnTestJni);

    }

    private void setEvent(AppCompatButton btnTestJni) {
        btnTestJni.setOnClickListener(v -> {
            int[] intArrayFromJni = createIntArray(30);
            System.err.println("intArrayFromJni ：" + Arrays.toString(intArrayFromJni));

            String[] stringArrayFromJni = createStringArray(6);
            System.err.println("stringArrayFromJni ：" + Arrays.toString(stringArrayFromJni));


            testJniAccessJavaStaticField();

        });

    }

    /**
     * jni 访问java的静态成员变量
     */
    private void testJniAccessJavaStaticField() {
        System.err.println("sName 的原始信息            : " + sName);
        accessJavaField();
        System.err.println("sName 在被jni 修改了以后的信息: " + sName);

    }

    /**
     * 使用JNI 创建一个int类型额数组
     *
     * @param size
     * @return
     */
    public native int[] createIntArray(int size);

    public native String[] createStringArray(int size);

    /**
     * 访问java层的成员变量
     */
    public native void accessJavaField();

}