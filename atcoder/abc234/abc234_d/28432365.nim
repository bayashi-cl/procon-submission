{.warning[UnusedImport]: off.}
import macros
import strutils
import sequtils
import strformat
import bitops
import math
import sugar
import std/heapqueue


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
    (n, k) = getInts().toTuple(2)
    p = getInts()

  var que = initHeapQueue[int]()

  for pi in p[0..<k]:
    que.push(pi)

  var ans = que.pop()
  echo ans
  for pi in p[k..<n]:
    if ans < pi:
      que.push(pi)
      ans = que.pop()
    echo ans

when is_main_module:
  main()
