{.warning[UnusedImport]: off.}
import macros
import strutils
import sequtils
import math
import sugar


macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym(); result = quote do: (let `t` = `arr`; ())
  for i in 0..<cnt: result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
proc getInt(): int {.used.} = stdin.readLine.parseInt
proc getInts(): seq[int] {.used.} = stdin.readLine.split.map(parseInt)

proc f(t: int): int =
  return t * t + 2 * t + 3

proc main() =
  let t = getInt()
  echo f(f(f(t) + t) + f(f(t)))

when is_main_module:
  main()
