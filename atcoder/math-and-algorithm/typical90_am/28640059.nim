{.warning[UnusedImport]: off.}
import macros, sugar
import math, bitops
import sequtils, strutils, strformat, algorithm
import sets, tables, deques

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do: (let `t` = `arr`; ())
  for i in 0..<cnt: result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
template `max=`*(x, y: typed): void = x = max(x, y)
template `min=`*(x, y: typed): void = x = min(x, y)
template `mod=`*(x, y: typed): void = x = x mod y
proc getInt(): int {.used.} = stdin.readLine.parseInt
proc getInts(): seq[int] {.used.} = stdin.readLine.split.map(parseInt)
proc print*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stdout.write(s)
proc debug*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stderr.write(s)
const Mod* = 1000000007
const IInf* = int.high div 2
let read* = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s

proc main() =
  let n = getInt()
  var graph = newSeqWith[n, newSeq[int]()]
  (n-1).times:
    let (a, b) = stdin.readLine.split.mapIt(parseInt(it) - 1).toTuple(2)
    graph[a].add(b)
    graph[b].add(a)

  var
    postOrder = newSeq[int]()
    edges = newSeq[(int, int)]()
  proc dfs(now: int, prev: int = -1) =
    edges.add((prev, now))
    for nxt in graph[now]:
      if nxt != prev:
        dfs(nxt, now)
    postOrder.add(now)
  dfs(0)

  var dp = newSeq[int](n)
  for now in postOrder:
    for nxt in graph[now]:
      dp[now] += dp[nxt]
    dp[now].inc

  var ans = 0
  for (f, t) in edges:
    ans += dp[t] * (n-dp[t])
  print(ans)

when is_main_module:
  main()
