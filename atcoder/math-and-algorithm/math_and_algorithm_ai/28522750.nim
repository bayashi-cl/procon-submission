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
  let (n, q) = getInts().toTuple(2)
  var a = getInts()
  # a.add(0)
  # a.rotateLeft(-1)
  for i in 1..<n:
    a[i] += a[i-1]
  q.times:
    let lr = getInts()
    if lr[0] == 1:
      echo a[lr[1]-1]
    else:
      echo a[lr[1]-1] - a[lr[0]-2]


when is_main_module:
  main()
