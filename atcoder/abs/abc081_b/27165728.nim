import strutils
import sequtils

discard readLine(stdin)
var a = readLine(stdin).split().map(parseInt)

proc cnt(xd: int): int =
  var x = xd
  while x mod 2 == 0:
    x = x div 2
    inc(result)

echo a.map(cnt).min()
