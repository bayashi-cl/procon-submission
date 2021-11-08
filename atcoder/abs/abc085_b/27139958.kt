fun main() {
    val n = readLine()!!.toInt()
    var s = mutableSetOf<Int>()
    repeat(n) {
        var d = readLine()!!.toInt()
        s.add(d)
    }
    println(s.size)
}
