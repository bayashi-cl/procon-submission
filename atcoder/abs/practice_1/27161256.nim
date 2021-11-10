import strutils
import sequtils

proc getInt(): int =
  parseInt(readLine(stdin))

proc getInts(): seq[int] =
  readLine(stdin).split().map(parseInt)

var a = getInt()
var
  b, c: int
(b, c) = getInts()
var s = readLine(stdin)

echo a + b + c, " ", s
