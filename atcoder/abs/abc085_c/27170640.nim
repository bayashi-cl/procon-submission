import strutils
import sequtils

var n, y: int
(n, y) = stdin.readLine.split.map(parseInt)

var ans = [-1, -1, -1]
for i in 0..n:
  for j in 0..(n - i):
    var k = n - i - j
    if 10000 * i + 5000 * j + 1000 * k == y:
      ans[0] = i; ans[1] = j; ans[2] = k


echo ans.join(" ")
