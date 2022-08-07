package com.jar.generateintarray;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import com.jar.generateintarray.databinding.ActivityMainBinding;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * 原文：https://mp.weixin.qq.com/s/i45NAQetqq-dcMxQqGI5yQ
 */
public class MainActivity extends AppCompatActivity {
    private Button btnTestJniAccessFiled;
    private Button btnTestJniInvokeJavaMethod;
    private Button btnTestNativeException;
    private static final String TAG = "MainActivity : ";


    static {
        System.loadLibrary("generateintarray");
    }

    private ActivityMainBinding binding;
    private static String sName = "java静态-->筱雅";
    private String mName = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        initView();
        initEvent();
    }

    private void initView() {
        btnTestJniAccessFiled = binding.btnTestJniAccessFiled;
        btnTestJniInvokeJavaMethod = binding.btnTestJniInvokeJavaMethod;
        btnTestNativeException = binding.btnTestNativeException;
    }

    private void initEvent() {
        btnTestJniAccessFiled.setOnClickListener(v -> {
            int[] intArrayFromJni = createIntArray(30);
            System.err.println("intArrayFromJni ：" + Arrays.toString(intArrayFromJni));

            String[] stringArrayFromJni = createStringArray(6);
            System.err.println("stringArrayFromJni ：" + Arrays.toString(stringArrayFromJni));
            testJniAccessJavaStaticField();
            testJniAccessJavaNormalField();

        });

        btnTestJniInvokeJavaMethod.setOnClickListener(v -> {
            invokeNormalJavaMethod();
            invokeStaticJavaMethod();
        });

        btnTestNativeException.setOnClickListener(v -> {

            try {
                throwExceptionByNative();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
            }
        });

    }

    /**
     * jni 访问java的普通成员变量
     */
    private void testJniAccessJavaNormalField() {
        accessJavaField();
        System.err.println("mName 在被jni 修改了以后的信息: " + mName);
    }

    /**
     * jni 访问java的静态成员变量
     */
    private void testJniAccessJavaStaticField() {
        accessJavaStaticField();
        System.err.println("sName 在被jni 修改了以后的信息: " + sName);
    }

    public static void helloOne(String str) {
        Log.e(TAG, " jni call the static  method :helloOne str : " + str);
    }

    public void helloTwo(ArrayList<String> rawData) {
        Log.e(TAG, " jni call the  normal method :and the  raw Data size is " + rawData.size());

        for (String rawDatum : rawData) {
            Log.e(TAG, "        " + rawDatum);
        }
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

    public native void accessJavaStaticField();

    /**
     * https://cloud.tencent.com/developer/article/1470677
     */
    public native void invokeNormalJavaMethod();

    public native void invokeStaticJavaMethod();

    public native void throwExceptionByNative();


}