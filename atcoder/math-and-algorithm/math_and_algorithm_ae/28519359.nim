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

const EPS = 1e-9
type Sgn = range[-1..1]
proc sgn(x: float): Sgn =
  if x < -EPS:
    return -1
  elif x > EPS:
    return 1
  else:
    return 0

type Point = object
  x, y: float64

proc initPoint(x, y: float): Point =
  return Point(x: x, y: y)

proc `+`(a, b: Point): Point {.used.} =
  result = Point(x: a.x + b.x, y: a.y + b.y)
proc `-`(a, b: Point): Point {.used.} =
  result = Point(x: a.x - b.x, y: a.y - b.y)
proc dot(a, b: Point): float64 =
  result = a.x * b.x + a.y * b.y
proc det(a, b: Point): float64 =
  result = a.x * b.y - a.y * b.x

proc norm(p: Point): float64 =
  return hypot(p.x, p.y)

type Segment = object
  p, q: Point

proc initSegment(a, b: Point): Segment =
  return Segment(p: a, q: b)

proc length(s: Segment): float64 =
  return (s.q-s.p).norm()

type Angle{.pure.} = enum
  Acute, Right, Obtuse

proc angle_type(a, b, c: Point): Angle =
  let t = sgn((a-b).dot(c-b))
  case t
  of -1:
    return Angle.Obtuse
  of 0:
    return Angle.Right
  of 1:
    return Angle.Acute

proc distance(p: Point, s: Segment): float64 =
  if angle_type(s.p, s.q, p) == Angle.Obtuse:
    return (p-s.q).norm()
  elif angle_type(s.q, s.p, p) == Angle.Obtuse:
    return (p-s.p).norm()
  else:
    return abs((s.q-s.p).det(p-s.p)) / s.length()


proc main() =
  let
    (ax, ay) = stdin.readLine.split.map(parseFloat).toTuple(2)
    (bx, by) = stdin.readLine.split.map(parseFloat).toTuple(2)
    (cx, cy) = stdin.readLine.split.map(parseFloat).toTuple(2)

    a = initPoint(ax, ay)
    b = initPoint(bx, by)
    c = initPoint(cx, cy)

    s = initSegment(b, c)

  echo a.distance(s)

when is_main_module:
  main()
