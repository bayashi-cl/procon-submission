fun check(x_: Int): Int {
    var x = x_
    var res = 0
    while (x > 0) {
        res += x % 10
        x /= 10
    }
    return res
}

fun main() {
    val (n, a, b) = readLine()!!.split(" ").map { it.toInt() }
    var ans = 0
    for (x in 1..n) {
        val sm = check(x)
        if (a <= sm && sm <= b) ans += x
    }
    println(ans)
}
