fun main() {
    readLine()
    var a = readLine()!!.split(" ").map { it.toInt() }.toMutableList()
    a.sortDescending()
    var alice = 0
    var bob = 0
    for (i in a.indices) {
        if (i % 2 == 0) {
            alice += a[i]
        } else {
            bob += a[i]
        }
    }
    println(alice - bob)
}
