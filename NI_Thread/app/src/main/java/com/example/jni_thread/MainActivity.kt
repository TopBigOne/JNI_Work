package com.example.jni_thread

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.example.jni_thread.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        initEvent()
    }

    //  git remote add origin git@github.com:TopBigOne/JNI_Work.git

    private fun initEvent() {
        binding.btnCreatePthread.setOnClickListener {
            Log.d(TAG, "initEvent: ----->")
            Toast.makeText(this@MainActivity, "dsdsgds", Toast.LENGTH_SHORT).show()

            startNormalThread()
        }

    }

    external fun startNormalThread()

    companion object {
        private const val TAG = "MainActivity :"
        init {
            System.loadLibrary("jni_thread")
        }
    }
}