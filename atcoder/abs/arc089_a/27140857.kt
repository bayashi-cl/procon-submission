import kotlin.math.abs

fun main() {
    var n = readLine()!!.toInt()
    var pos = arrayOf(0, 0)
    var time = 0
    repeat(n) {
        var (t, x, y) = readLine()!!.split(" ").map { it.toInt() }
        val dt = t - time
        val dx = abs(pos[0] - x)
        val dy = abs(pos[1] - y)
        if (dx + dy > dt) {
            println("No")
            return
        }
        if ((dx + dy) % 2 != dt % 2) {
            println("No")
            return
        }
        pos = arrayOf(x, y)
        time = t
    }
    println("Yes")
}
