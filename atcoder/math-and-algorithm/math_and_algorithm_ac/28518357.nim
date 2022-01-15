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
    a = getInts()

  var dp = newSeqWith(n+1, newSeq[int](2))
  for i in 1..n:
    dp[i][0] = dp[i-1].max()
    dp[i][1] = dp[i-1][0] + a[i-1]
  echo dp[n].max()

when is_main_module:
  main()
