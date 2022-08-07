package com.jar.coroutine

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.withContext

/**
 * @author  : dev
 * @version :
 * @Date    :  2022/8/6 14:49
 * @Desc    :
 *
 */
object SuspendFunction {

    suspend fun add(a: Int, b: Int): Int {
        return withContext(Dispatchers.Default) {

            delay(2000)
            a + b
        }
    }
}