{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm

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
    p = newSeqWith(n, getInts().toTuple(2))

  var ss = 1e18.toInt()
  for i in 0..<n:
    for j in i+1..<n:
      let
        dx = p[i][0] - p[j][0]
        dy = p[i][1] - p[j][1]
      ss = min(ss, dx^2 + dy^2)

  echo sqrt(ss.toFloat())

when is_main_module:
  main()
