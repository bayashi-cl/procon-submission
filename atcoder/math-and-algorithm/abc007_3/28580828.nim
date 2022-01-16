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
const IINF* = int.high div 2


proc main() =
  let
    (r, c) = getInts().toTuple(2)
    (sy, sx) = getInts().toTuple(2)
    (gy, gx) = getInts().toTuple(2)
    b = newSeqWith(r, stdin.readLine())
    delta = @[(0, 1), (1, 0), (0, -1), (-1, 0)]
  proc index(i, j: int): int = i * c + j
  var graph = newSeqWith(r * c, newSeq[int]())
  let
    s = index(sy-1, sx-1)
    g = index(gy-1, gx-1)

  for i in 0..<r:
    for j in 0..<c:
      if b[i][j] == '#':
        continue
      for (di, dj) in delta:
        let
          ni = i + di
          nj = j + dj
        if ni < 0 or r <= ni:
          continue
        if nj < 0 or c <= nj:
          continue
        if b[ni][nj] == '.':
          graph[index(i, j)].add(index(ni, nj))

  var
    cost = newSeqWith(r*c, IINF)
    que = initDeque[int]()
  que.addLast(s)
  cost[s] = 0
  while que.len() != 0:
    let top = que.popFirst()
    for nxt in graph[top]:
      if cost[nxt] == IINF:
        cost[nxt] = cost[top] + 1
        que.addLast(nxt)

  print(cost[g])

when is_main_module:
  main()
