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

proc main() =
  let
    s = stdin.readLine.map(x => ord(x))
    t = stdin.readLine.map(x => ord(x))
    d = (t[0] - s[0] + 26) mod 26

  for (si, ti) in zip(s, t):
    if (ti - si + 26) mod 26 != d:
      echo "No"
      return

  echo "Yes"


when is_main_module:
  main()
