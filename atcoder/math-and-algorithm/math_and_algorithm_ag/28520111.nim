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
  const EPS = 1e-9
  var
    (x1, y1, r1) = stdin.readLine.split.map(parseFloat).toTuple(3)
    (x2, y2, r2) = stdin.readLine.split.map(parseFloat).toTuple(3)

    d = hypot(x1-x2, y1-y2)

  if d - (r1+r2) > EPS:
    echo 5
  elif d - (r1+r2) > -EPS:
    echo 4
  else:
    if r1 < r2:
      swap(r1, r2)

    if d+r2-r1 < -EPS:
      echo 1
    elif d+r2-r1 > EPS:
      echo 3
    else:
      echo 2


when is_main_module:
  main()
