package com.example.jni_thread

import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.jni_thread.databinding.ActivityMainBinding


/**
 * https://github.com/wanliyang1990/Android-JniThread
 */
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

        binding.btnPAndC.setOnClickListener {
            startMutexThread()
        }
        binding.btnPthreadCallback.setOnClickListener {
            starPThreadCallback()
        }
    }

    external fun startNormalThread()
    external fun startMutexThread()
    external fun starPThreadCallback()

    companion object {
        private const val TAG = "MainActivity :"

        init {
            System.loadLibrary("jni_thread")
        }
    }


    //Jni调用此方法，把结果返回到java层
    fun onError(code: Int, msg: String?) {
        Log.d(TAG, "onError: thread : " + Thread.currentThread().name)
        Log.d("ywl5320", "code: $code, msg: $msg");
        //  onErrorListener.onError(code, msg)
    }


}