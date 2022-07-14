package com.example.epplldemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.epplldemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'epplldemo' library on application startup.
    static {
        System.loadLibrary("epplldemo");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        initEvent();


    }

    private void initEvent() {
        binding.btnTestEpoll.setOnClickListener(v -> {
            exeEpoll();
        });

    }
    public native void exeEpoll();
}