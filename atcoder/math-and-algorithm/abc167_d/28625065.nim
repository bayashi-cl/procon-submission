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
let read* = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s

proc main() =
  let
    n, k = read().parseInt()
    a = stdin.readLine.split.mapIt(parseInt(it) - 1)
    l = fastLog2(k) + 1

  var db = newSeqWith(l+1, newSeq[int](n))
  for i, ai in a: db[0][i] = a[i]
  for i in 0..<l:
    for j in 0..<n:
      db[i+1][j] = db[i][db[i][j]]

  var ans = 0
  for d in 0..<l:
    if k.testBit(d):
      ans = db[d][ans]

  print(ans+1)

when is_main_module:
  main()
