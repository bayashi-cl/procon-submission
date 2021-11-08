fun main() {
    var (n, y) = readLine()!!.split(" ").map { it.toInt() }
    for (a in 0..n) {
        for (b in 0..n - a) {
            val c = n - a - b
            if (10000 * a + 5000 * b + 1000 * c == y) {
                println("$a $b $c")
                return
            }
        }
    }
    println("-1 -1 -1")
}
