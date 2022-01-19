{.warning[UnusedImport]: off.}
import macros, sugar
import math, bitops
import sequtils, strutils, strformat, algorithm
import sets, tables, deques, heapqueue

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

type
  Node = tuple
    dest: int
    weight: int

proc `<`*(a, b: Node): bool =
  result = a.weight < b.weight

proc initNode(d: int, c: int): Node =
  return (dest: d, weight: c)


proc dijkstra(graph: seq[seq[Node]], start: int): seq[int] =
  let n = len(graph)
  var que = initHeapQueue[Node]()
  result = newSeqWith(n, IInf)
  que.push(initNode(start, 0))
  while que.len > 0:
    let top = que.pop()
    for nxt in graph[top.dest]:
      let nxtCost = top.weight + nxt.weight
      if nxtCost < result[nxt.dest]:
        result[nxt.dest] = nxtCost
        que.push(initNode(nxt.dest, nxtCost))

proc main() =
  let n, m = read().parseInt()
  var graph = newSeqWith(n, newSeq[Node]())
  m.times:
    let a, b, c = read().parseInt()
    graph[a - 1].add(initNode(b - 1, c))
    graph[b - 1].add(initNode(a - 1, c))

  let
    res = dijkstra(graph, 0)
    ans = res[res.high]
  print(if ans == IInf: -1 else: ans)

when is_main_module:
  main()
