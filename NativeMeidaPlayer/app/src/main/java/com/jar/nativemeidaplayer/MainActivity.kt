package com.jar.nativemeidaplayer

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.activity.result.contract.ActivityResultContracts
import com.jar.nativemeidaplayer.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        //   binding.sampleText.text = stringFromJNI()
    }

    /**
     * 点击事件
     */
    fun onSelectVideo(view: View) {
        requestPermission.launch(android.Manifest.permission.READ_EXTERNAL_STORAGE)
    }

    private val selectorVideoLauncher = registerForActivityResult(ActivityResultContracts.GetContent()) { uri ->
        val path = uri?.let {
            PictureUtil.getPath(this, it)
        }
        path?.let {
            LocalPlayerActivity.player(this, it)
        }
    }

    private val requestPermission = registerForActivityResult(ActivityResultContracts.RequestPermission()) { isGrant ->
        if(isGrant) {
            selectorVideoLauncher.launch("video/*")
        }
    }

    companion object {

        init {

        }
    }
}