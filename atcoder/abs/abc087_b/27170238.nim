import strutils
# import sequtils

var a = parseInt(readLine(stdin))
var b = parseInt(readLine(stdin))
var c = parseInt(readLine(stdin))
var x = parseInt(readLine(stdin))


var ans = 0

for i in countup(0, a):
  for j in countup(0, b):
    for k in countup(0, c):
      if 500 * i + 100 * j + 50 * k == x:
        inc(ans)

echo ans
