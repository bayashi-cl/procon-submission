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

# func isqrt(x: int): int =
#   result = 0
#   var q = 1

#   while q <= x:
#     q = q shl 2

#   var z = x
#   while q > 1:
#     q = q shr 2
#     let t = z - result - q
#     result = result shr 1
#     if t >= 0:
#       z = t
#       result += q

# proc divisor(n: int): seq[int] =
#   var
#     lower = newSeq[int]()
#     upper = newSeq[int]()

#   for d in 1..isqrt(n):
#     if n mod d == 0:
#       lower.add(d)
#       if d * d != n:
#         upper.add(n div d)

#   upper.reverse()
#   return lower.concat(upper)

proc ceilDiv*[T: SomeInteger](x, y: T): T {.inline.} =
  result = x div y
  if not (x < 0 xor y < 0) and x mod y != 0:
    inc result

proc main() =
  let a, b = read().parseInt()
  var ans = 1
  for i in 1..b-a:
    let
      l = ceilDiv(a, i)
      r = b div i
    if l != r: ans.max = i
  print(ans)


when is_main_module:
  main()
