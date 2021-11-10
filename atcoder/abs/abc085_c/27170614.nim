import strutils
import sequtils
import strformat

var n, y: int
(n, y) = stdin.readLine.split.map(parseInt)

var (a, b, c) = (-1, -1, -1)
for i in 0..n:
  for j in 0..(n - i):
    var k = n - i - j
    if 10000 * i + 5000 * j + 1000 * k == y:
      a = i
      b = j
      c = k

echo fmt"{a} {b} {c}"
