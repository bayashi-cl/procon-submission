import macros
import posix
import strutils
import sequtils

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym(); result = quote do: (let `t` = `arr`; ())
  for i in 0..<cnt: result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)

var n = stdin.readLine.parseInt
var time, x, y: int

n.times:
  var
    (t, xi, yi) = stdin.readLine.split.map(parseInt).toTuple(3)
    dt = t - time
    dd = abs(xi - x) + abs(yi - y)

  if dt < dd or dt mod 2 != dd mod 2:
    echo "No"
    exitnow(0)

  time = t; x = xi; y = yi

echo "Yes"
