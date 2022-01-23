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
  var b = newSeqWith(2*n, newSeq[int](2*n))
  for i in 0..<2*n:
    for j in i+1..<2*n:
      b[i][j] = read().parseInt()

  let MX = 1 shl (2 * n)
  var ans = -1

  proc dfs(s, c: int) =
    if s == MX - 1:
      ans.max = c
    var f = -1
    for d in 0..<2*n:
      if testBit(s, d): continue
      if f == -1:
        f = d
      else:
        dfs(s or (1 shl f) or (1 shl d), c xor b[f][d])

  dfs(0, 0)
  print(ans)

when is_main_module:
  main()
