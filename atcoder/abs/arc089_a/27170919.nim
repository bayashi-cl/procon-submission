import posix
import strutils
import sequtils

var n = stdin.readLine.parseInt

var time, x, y: int

for i in 0..<n:
  var t, xi, yi: int
  (t, xi, yi) = stdin.readLine.split.map(parseInt)
  var
    dt = t - time
    dd = abs(xi - x) + abs(yi - y)

  if dt < dd or dt mod 2 != dd mod 2:
    echo "No"
    exitnow(0)

  time = t; x = xi; y = yi

echo "Yes"
