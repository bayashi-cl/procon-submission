import java.math.BigDecimal
import java.math.RoundingMode

fun main() {
    val x = BigDecimal(readLine()!!)
    println(x.setScale(0, RoundingMode.HALF_UP))
}
