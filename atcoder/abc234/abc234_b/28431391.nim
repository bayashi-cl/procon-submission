{.warning[UnusedImport]: off.}
import macros
import strutils
import sequtils
import strformat
import math
import sugar


macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
proc getInt(): int {.used.} = stdin.readLine.parseInt
proc getInts(): seq[int] {.used.} = stdin.readLine.split.map(parseInt)

proc main() =
  let
    n = getInt()
    xy = newSeqWith(n, getInts().toTuple(2))

  var ans = 0.0

  for i in 0..<n:
    for j in i+1..<n:
      let
        dx = (xy[j][0] - xy[i][0]).toFloat()
        dy = (xy[j][1] - xy[i][1]).toFloat()
      ans = max(ans, hypot(dx, dy))

  echo ans

when is_main_module:
  main()
