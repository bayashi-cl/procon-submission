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

proc powMod*(a, b, m: int): int =
  result = 1
  var p = a
  for d in 0..fastLog2(b):
    if b.testBit(d):
      result *= p
      result = result mod m
    p = (p^2) mod m

proc comb*(n, r, m: int): int =
  var
    num = 1
    den = 1
  for i in 0..<min(r, n - r):
    num *= n - i
    num.mod = m
    den *= i + 1
    den.mod = m

  den = den.powMod(m-2, m)
  return num * den mod m

proc main() =
  let x, y = read().parseInt()
  if (x + y) mod 3 != 0:
    print(0)
    return
  let move = (x + y) div 3
  if x < move or y < move:
    print(0)
    return

  print(comb(move, x - move, Mod))

when is_main_module:
  main()
