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
  let (n, m) = getInts().toTuple(2)
  var graph = newSeqWith(n, newSeq[int]())
  m.times:
    let (a, b) = stdin.readLine.split.mapIt(parseInt(it) - 1).toTuple(2)
    graph[a].add(b)
    graph[b].add(a)

  var
    que = initDeque[int]()
    cost = newSeqWith(n, IInf)
  que.addLast(0)
  cost[0] = 0

  while que.len > 0:
    let top = que.popFirst()
    for nxt in graph[top]:
      if cost[nxt] > cost[top] + 1:
        cost[nxt] = cost[top] + 1
        que.addLast(nxt)

  for ci in cost: print(min(ci, 120))


when is_main_module:
  main()
