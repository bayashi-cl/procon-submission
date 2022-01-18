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
  let
    n, k = read().parseInt()
    xy = newSeqWith(n, getInts().toTuple(2))
  # if n == 2:
  #   print(abs(xy[0][0]-xy[1][0]) * abs(xy[0][1]-xy[1][1]))
  # elif n == 3:
  #   var ans = IInf
  #   if k == 2:
  #     for i in 0..<n:
  #       for j in 0..<n:
  #         ans.min = abs(xy[i][0]-xy[i][0]) * abs(xy[j][1]-xy[j][1])
  #   else:
  #     var
  #       l = IInf
  #       r = -IInf
  #       d = IInf
  #       u = -IInf
  #     for (x, y) in xy:
  #       l.min = x
  #       r.max = x
  #       d.min = y
  #       u.max = y
  #     ans.min = (r-l) * (u-d)
  # else:
  var ans = IInf
  for e in 0..<n:
    for f in 0..<n:
      for g in 0..<n:
        for h in 0..<n:
          var
            l = IInf
            r = -IInf
            d = IInf
            u = -IInf
          for i in [e, f, g, h]:
            let (x, y) = xy[i]
            l.min = x
            r.max = x
            d.min = y
            u.max = y
          var cnt = 0
          for (x, y) in xy:
            if l <= x and x <= r and d <= y and y <= u:
              cnt.inc
          if cnt >= k:
            ans.min = (r-l) * (u-d)

  print(ans)

when is_main_module:
  main()
