{.warning[UnusedImport]: off.}
import macros
import strutils
import sequtils
import strformat
import bitops
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
    k: int = getInt()
    kb: string = k.toBin(fastLog2(k) + 1)
  echo kb.replace('1', '2')


when is_main_module:
  main()
