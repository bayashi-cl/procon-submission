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
    (n, w) = getInts().toTuple(2)
    wv = newSeqWith(n, getInts().toTuple(2))

  var dp = newSeqWith(n + 1, newSeq[int](w + 1))
  for i in 1..n:
    let (wi, vi) = wv[i-1]
    for j in 0..w:
      dp[i][j] = dp[i-1][j]
      if j - wi >= 0:
        dp[i][j] = max(dp[i][j], dp[i-1][j-wi] + vi)

  echo dp[n].max()

when is_main_module:
  main()
