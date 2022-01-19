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
  const Eps = 1e-8
  let
    n = getInt()
    abc = newSeqWith(n, getInts().toTuple(3))

  var ans = 0.0
  for i in 0..<n:
    for j in i+1..<n:
      let
        (a, b, c) = abc[i]
        (p, q, r) = abc[j]
      if p * b - q * a == 0: continue
      let
        x = (c*q - r*b) / (a*q - p*b)
        y = (c*p - r*a) / (b*p - q*a)

      var flg = true
      for (s, t, u) in abc:
        if s.toFloat*(x-Eps) + t.toFloat*(y-Eps) > u.toFloat:
          flg = false
          break
      if flg: ans.max = x+y

  print(ans)

when is_main_module:
  main()
