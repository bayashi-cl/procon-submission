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

proc ceilDiv*[T: SomeInteger](x, y: T): T {.inline.} =
  result = x div y
  if not (x < 0 xor y < 0) and x mod y != 0:
    inc result

func isqrt(x: int): int =
  result = 0
  var q = 1

  while q <= x:
    q = q shl 2

  var z = x
  while q > 1:
    q = q shr 2
    let t = z - result - q
    result = result shr 1
    if t >= 0:
      z = t
      result += q

proc main() =
  let l, r = read().parseInt()
  var s = newSeqWith(r - l + 1, 1)
  proc minDiv(d: int): int = result = ceilDiv(l, d) * d
  proc maxDiv(d: int): int = result = r div d * d

  if l == 1: s[0] = 0
  for i in countup(minDiv(2), maxDiv(2), 2):
    if i == 2: continue
    s[i - l] = 0
  for p in countup(3, isqrt(r), 2):
    for i in countup(minDiv(p), maxDiv(p), p):
      if i == p: continue
      s[i - l] = 0

  print(s.sum())



when is_main_module:
  main()
