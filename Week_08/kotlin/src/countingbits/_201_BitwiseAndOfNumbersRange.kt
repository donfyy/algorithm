package countingbits

fun rangeBitwiseAnd(m: Int, n: Int): Int {
    var ret = n
    while (m < ret) {
        ret = ret and ret - 1
    }
    return ret
}

class _201_Shift_ {
    fun rangeBitwiseAnd(m: Int, n: Int): Int {
        var a = m
        var b = n
        var shift = 0
        while (a != b) {
            a = a ushr 1
            b = b ushr 1
            shift++
        }
        return a shl shift
    }
}