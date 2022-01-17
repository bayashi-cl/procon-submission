{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm, deques

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
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
const IINF = int.high div 2


type
  ZeroOne = range[0..1]
  Node = tuple
    dest: int
    cost: ZeroOne

proc initNode(d: int, c: ZeroOne): Node =
  return (dest: d, cost: c)

proc zeroOneBFS(graph: seq[seq[Node]], start: int): seq[int] =
  var
    que = initDeque[int]()
    cost = newSeqWith(graph.len(), IINF)
  que.addLast(start)
  cost[start] = 0
  while que.len > 0:
    let top = que.popFirst()
    for nxt in graph[top]:
      let dist = cost[top] + nxt.cost
      if dist < cost[nxt.dest]:
        cost[nxt.dest] = dist

        case nxt.cost
        of 0:
          que.addFirst(nxt.dest)
        of 1:
          que.addLast(nxt.dest)

  return cost

proc main() =
  let k = getInt()
  var graph = newSeqWith(k, newSeq[Node]())

  for i in 1..<k:
    graph[i].add(initNode((i+1) mod k, 1))
    graph[i].add(initNode((i*10) mod k, 0))

  let cost = zeroOneBFS(graph, 1)
  print(cost[0]+1)

when is_main_module:
  main()
