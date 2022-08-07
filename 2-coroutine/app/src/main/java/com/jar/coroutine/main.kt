package com.jar.coroutine

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

/**
 * @author  : dev
 * @version :
 * @Date    :  2022/8/6 14:50
 * @Desc    : https://www.bilibili.com/video/BV1zz411v78d?spm_id_from=333.337.search-card.all.click&vd_source=48ebba24d97534cb7fc891ea4972fffa
 *
 */
fun main() {
    GlobalScope.launch {
        val a = SuspendFunction.add(1, 2)
        val b = SuspendFunction.add(4, 5)
        println("a : $a")
        println("b : $b")
    }

    readLine()

}