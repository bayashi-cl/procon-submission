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
const INF* {.used.} = int.high div 2




proc main() =
  let (n, m) = getInts().toTuple(2)

  var graph = newSeqWith(n, newSeq[int]())
  m.times:
    var (a, b) = getInts().toTuple(2)
    graph[a-1].add(b-1)
    graph[b-1].add(a-1)

  var
    cost = newSeqWith(n, INF)
    que = initDeque[int]()
  cost[0] = 0
  que.addLast(0)

  while que.len > 0:
    let top = que.popFirst()
    for dest in graph[top]:
      if cost[dest] == INF:
        cost[dest] = cost[top] + 1
        que.addLast(dest)

  for c in cost:
    if c == INF:
      print(-1)
    else:
      print(c)

when is_main_module:
  main()
