{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm, sets, tables

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
    _ = getInt()
    a = getInts()
    cnt = a.toCountTable()
  let h = cnt.getOrDefault(50000)
  var ans = h * (h - 1) div 2
  for i in 1..49999:
    ans = ans + cnt.getOrDefault(i) * cnt.getOrDefault(100000 - i)

  echo ans

when is_main_module:
  main()
