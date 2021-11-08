fun main() {
    val (a, b) = readLine()!!.split(" ").map { it.toInt() }
    if (a * b % 2 == 0) println("Even") else println("Odd")
}
