import strutils
import sequtils

var
  n, a, b: int
(n, a, b) = readLine(stdin).split().map(parseInt)

proc digsum(xx: int): int =
  var x = xx
  while x > 0:
    result += x mod 10
    x = x div 10

var ans = 0
for i in countup(1, n):
  var sm = digsum(i)
  if a <= sm and sm <= b:
    ans += i

echo ans
