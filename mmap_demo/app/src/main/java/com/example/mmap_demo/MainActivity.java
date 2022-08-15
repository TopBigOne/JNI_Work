package com.example.mmap_demo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.mmap_demo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'mmap_demo' library on application startup.
    static {
        System.loadLibrary("mmap_demo");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method

        initEvent();
    }

    private void initEvent() {
        binding.btnTestMmapOne.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testMMAp();
            }
        });


    }

    /**
     * A native method that is implemented by the 'mmap_demo' native library,
     * which is packaged with this application.
     */
    public native String testMMAp();
}