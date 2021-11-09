fun main() {
    val n = readLine()!!.toInt()
    var a = mutableListOf<List<Int>>()
    var t = MutableList<Int>(n) { 0 }
    repeat(n) {
        val line = readLine()!!.split(" ").map { it.toInt() }
        t[it] = line[0]
        val ai = line.drop(2).map { it - 1 }
        a.add(ai)
    }
    var skill = mutableSetOf(n - 1)
    for (i in n - 1 downTo 0) {
        if (!skill.contains(i)) continue
        for (aij in a[i]) skill.add(aij)
    }
    var ans = 0L
    for (si in skill) ans += t[si]
    println(ans)
}
