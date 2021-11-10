import strutils
import sequtils
import algorithm

var
  n = stdin.readLine.parseInt
  a = stdin.readLine.split.map(parseInt)

a.sort(Descending)
var alice, bob: int
for i in 0..<n:
  if i mod 2 == 0:
    alice += a[i]
  else:
    bob += a[i]

echo alice - bob
