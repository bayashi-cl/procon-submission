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

type Point = object
  x, y: int

# proc initPoint(x, y: int): Point =
#   return Point(x: x, y: y)
proc toPoint(t: tuple): Point =
  return Point(x: t[0], y: t[1])

proc `+`(a, b: Point): Point {.used.} =
  result = Point(x: a.x + b.x, y: a.y + b.y)
proc `-`(a, b: Point): Point {.used.} =
  result = Point(x: a.x - b.x, y: a.y - b.y)
# proc dot(a, b: Point): int =
#   result = a.x * b.x + a.y * b.y
proc det(a, b: Point): int =
  result = a.x * b.y - a.y * b.x
# proc swap(a,b:Point)

proc main() =
  let
    n = getInt()
    polygon = newSeqWith(n, getInts().toTuple(2).toPoint())
    o = getInts().toTuple(2).toPoint()

  var ins = false
  for i in 0..<n:
    var
      a = polygon[i] - o
      b = polygon[(i+1) mod n] - o
    if a.y > b.y: swap(a, b)
    if a.y <= 0 and 0 < b.y and a.det(b) < 0: ins = not ins

  print(if ins: "INSIDE" else: "OUTSIDE")

when is_main_module:
  main()
