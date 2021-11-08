fun main() {
    var s = readLine()!!
    var flg = true
    while (!s.isEmpty() && flg) {
        when {
            s.endsWith("dreamer") -> s = s.substring(0, s.lastIndexOf("dreamer"))
            s.endsWith("eraser") -> s = s.substring(0, s.lastIndexOf("eraser"))
            s.endsWith("dream") -> s = s.substring(0, s.lastIndexOf("dream"))
            s.endsWith("erase") -> s = s.substring(0, s.lastIndexOf("erase"))
            else -> flg = false
        }
    }
    println(if (flg) "YES" else "NO")
}
