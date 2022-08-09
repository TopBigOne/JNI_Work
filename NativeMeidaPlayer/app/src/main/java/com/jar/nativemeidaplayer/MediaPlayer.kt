package com.jar.nativemeidaplayer

import android.util.Log
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleEventObserver
import androidx.lifecycle.LifecycleOwner

/**
 * @author  : dev
 * @version :
 * @Date    :  2022/8/7 19:15
 * @Desc    :
 *
 */
class MediaPlayer(lifecycleOwner: LifecycleOwner) : LifecycleEventObserver {

    // Native 层指针
    private var nativeObj: Long? = null
    var videoPath: String? = null

    companion object {
        private const val TAG = "MediaPlayer : "

        init {
            System.loadLibrary("nativemeidaplayer")
        }
    }

    init {
        lifecycleOwner.lifecycle.addObserver(this);
    }

    fun start(path: String) {
        // 注意点：记录 Native 层指针，后续操作才能拿到 Native 的对象
        //  nativeObj = startNative(path)
    }

    fun stop() {

    }


    fun release() {
        // 注意点：使用 start() 中记录的指针调用 native 方法
        nativeObj?.let {
            releaseNative(it)
        }
        nativeObj = null
    }


    override fun onStateChanged(source: LifecycleOwner, event: Lifecycle.Event) {
        when (event) {
            Lifecycle.Event.ON_RESUME -> {

            }
            Lifecycle.Event.ON_STOP -> {
                nativeObj?.let {
                    startNative(it)
                }

            }
            Lifecycle.Event.ON_DESTROY -> {
                nativeObj?.let {
                    releaseNative(it)
                }
            }
        }
    }

    fun restart() {
        videoPath?.let {
            nativeObj = prepareNative(it)
        }
    }

    fun onPrepared() {
        nativeObj?.let {
            Log.i("XIAOPENG", "prepared")
            startNative(it)
        }
    }


    private external fun prepareNative(videoPath: String): Long
    private external fun releaseNative(ptr: Long)
    private external fun startNative(ptr: Long)
    private external fun stopNative(ptr: Long)

}