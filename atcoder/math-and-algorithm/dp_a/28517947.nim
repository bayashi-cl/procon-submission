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
    h = getInts()

  var dp = newSeq[int](n)
  dp[0] = 0
  dp[1] = abs(h[0] - h[1])
  for x in 2..dp.high:
    dp[x] = min(dp[x - 1] + abs(h[x] - h[x - 1]), dp[x - 2] + abs(h[x] - h[x - 2]))
  echo dp[n-1]
  # var memo = newSeqWith(n, -1)
  # memo[0] = 0
  # memo[1] = abs(h[0] - h[1])
  # proc dp(x: int): int =
  #   if memo[x] != -1:
  #     return memo[x]

  #   result = min(dp(x - 1) + abs(h[x] - h[x - 1]), dp(x - 2) + abs(h[x] - h[x - 2]))
  #   memo[x] = result

  # echo dp(n - 1)

when is_main_module:
  main()
