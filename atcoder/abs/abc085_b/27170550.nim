# import sequtils
import strutils
import sets

var n = stdin.readLine.parseInt
var s = initHashSet[int]()

for i in 0..<n:
  var di = stdin.readLine.parseInt
  s.incl(di)

echo s.len
