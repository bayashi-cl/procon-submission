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
  var cnt = a.toCountTable()
  var ans = 0
  ans = ans + cnt.getOrDefault(100) * cnt.getOrDefault(400)
  ans = ans + cnt.getOrDefault(200) * cnt.getOrDefault(300)
  echo ans

when is_main_module:
  main()
