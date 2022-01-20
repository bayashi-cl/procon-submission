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
template `div=`*(x, y: typed): void = x = x div y
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

proc col(a, b: int): int =
  if a == b:
    result = a
  else:
    result = 3 - a - b

proc main() =
  var
    n = getInt()
    cs = stdin.readLine()
    c = newSeq[int](n)
  for i, ci in cs:
    if ci == 'B':
      c[i] = 0
    elif ci == 'W':
      c[i] = 1
    else:
      c[i] = 2

  n.dec
  var w = 1
  while n > 0:
    let t = n mod 3
    t.times:
      var nc = newSeq[int]()
      for i in 0..<c.len-w:
        nc.add(col(c[i], c[i+w]))
      c = nc
    n.div = 3
    w *= 3

  if c[0] == 0:
    print("B")
  elif c[0] == 1:
    print("W")
  else:
    print("R")

when is_main_module:
  main()
