fun main() {
    val n = readLine()!!.toInt()
    var s = mutableSetOf<List<Int>>()
    repeat(n) {
        val a = readLine()!!.split(" ").drop(1).map { it.toInt() }
        s.add(a)
    }
    println(s.size)
}
