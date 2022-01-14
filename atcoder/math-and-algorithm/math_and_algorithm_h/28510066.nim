{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar

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
  let (n, s) = getInts().toTuple(2)
  var ans = 0
  for a in 1..n:
    for b in 1..n:
      if a + b <= s:
        ans += 1
  echo ans


when is_main_module:
  main()
