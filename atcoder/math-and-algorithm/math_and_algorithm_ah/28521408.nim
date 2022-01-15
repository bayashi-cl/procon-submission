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
proc getFloat(): float {.used.} = stdin.readLine.parseFloat
proc getFloats(): seq[float] {.used.} = stdin.readLine.split.map(parseFloat)

# const EPS = 1e-9
# type Sgn = range[-1..1]
# proc sgn(x: float): Sgn =
#   if x < -EPS:
#     return -1
#   elif x > EPS:
#     return 1
#   else:
#     return 0

type Point = object
  x, y: int

proc initPoint(x, y: int): Point =
  return Point(x: x, y: y)

proc `+`(a, b: Point): Point {.used.} =
  result = Point(x: a.x + b.x, y: a.y + b.y)
proc `-`(a, b: Point): Point {.used.} =
  result = Point(x: a.x - b.x, y: a.y - b.y)
proc dot(a, b: Point): int =
  result = a.x * b.x + a.y * b.y
proc det(a, b: Point): int =
  result = a.x * b.y - a.y * b.x

type Dir = range[-2..2]

proc iSP(a, b, c: Point): Dir =
  let s = (b-a).det(c-a)
  if s > 0:
    return 1
  elif s < 0:
    return -1
  else:
    if (b - a).dot(c - b) > 0:
      return 2
    elif (a - b).dot(c - a) > 0:
      return -2
    else:
      return 0

type Segment = object
  p, q: Point

proc initSegment(a, b: Point): Segment =
  return Segment(p: a, q: b)

proc iSP(s: Segment, p: Point): Dir =
  return iSP(s.p, s.q, p)

proc isCross(a, b: Segment): bool =
  return a.iSP(b.p) * a.iSP(b.q) <= 0 and b.iSP(a.p) * b.iSP(a.q) <= 0

proc main() =
  let
    (x1, y1) = getInts().toTuple(2)
    (x2, y2) = getInts().toTuple(2)
    (x3, y3) = getInts().toTuple(2)
    (x4, y4) = getInts().toTuple(2)

    s1 = initSegment(initPoint(x1, y1), initPoint(x2, y2))
    s2 = initSegment(initPoint(x3, y3), initPoint(x4, y4))

  echo if is_cross(s1, s2): "Yes" else: "No"

when is_main_module:
  main()
