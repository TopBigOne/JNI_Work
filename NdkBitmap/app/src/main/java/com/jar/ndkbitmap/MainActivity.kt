package com.jar.ndkbitmap

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.ImageView
import androidx.tracing.trace
import com.jar.ndkbitmap.databinding.ActivityMainBinding
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    lateinit var btnOne: Button
    lateinit var imgOne: ImageView
    lateinit var imgTwo: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        btnOne = binding.btnCreateBitmap
        imgOne = binding.imgOne
        imgTwo = binding.imgTwo
        imgOne.setImageResource(R.mipmap.two)

        initEvent()
    }

    private fun initEvent() {
        btnOne.setOnClickListener {

            createBitmapByNative()
        }
    }

    private fun createBitmapByNative() {
        trace("TAG_createBitmapByNative") {

            val newBitmap = BitmapFactory.decodeResource(resources, R.mipmap.two)
            passBitmap(newBitmap)
            imgTwo.setImageBitmap(newBitmap);
        }
    }

    /**
     * A native method that is implemented by the 'ndkbitmap' native library,
     * which is packaged with this application.
     */

    private external fun passBitmap(bitmap: Bitmap)

    companion object {
        const val TAG = "xiao_ya_MainActivity"

        // Used to load the 'ndkbitmap' library on application startup.
        init {
            System.loadLibrary("ndkbitmap")
        }
    }
}