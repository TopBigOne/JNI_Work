package com.jar.generateintarray;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.jar.generateintarray.databinding.ActivityMainBinding;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'generateintarray' library on application startup.
    static {
        System.loadLibrary("generateintarray");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        // Example of a call to a native method
        TextView tv = binding.sampleText;
        int[] intArrayFromJni = createIntArray(30);
        System.err.println("intArrayFromJni ：" + Arrays.toString(intArrayFromJni));

        String[] stringArrayFromJni = createStringArray(6);
        System.err.println("stringArrayFromJni ：" + Arrays.toString(stringArrayFromJni));
    }

    /**
     * 使用JNI 创建一个int类型额数组
     *
     * @param size
     * @return
     */
    public native int[] createIntArray(int size);

    public native String[] createStringArray(int size);

}