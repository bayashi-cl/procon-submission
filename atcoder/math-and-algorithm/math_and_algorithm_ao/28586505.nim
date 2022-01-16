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
proc print*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stdout.write(s)
proc debug*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stderr.write(s)

proc main() =
  let (n, m) = getInts().toTuple(2)
  var graph = newSeqWith(n, newSeq[int]())
  m.times:
    let (a, b) = stdin.readLine.split.mapIt(parseInt(it)-1).toTuple(2)
    graph[a].add(b)
    graph[b].add(a)

  var color = newSeq[int](n)

  proc dfs(now, col: int) =
    color[now] = col
    for nxt in graph[now]:
      if color[nxt] == col:
        print("No")
        quit(QuitSuccess)
      if color[nxt] == 0:
        dfs(nxt, 3-col)

  for i in 0..<n:
    if color[i] == 0:
      dfs(i, 1)
  print("Yes")

when is_main_module:
  main()
