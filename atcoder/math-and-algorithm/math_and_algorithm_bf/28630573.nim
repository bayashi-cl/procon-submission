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
  let n = getInt()
  var
    a = newSeq[float64](n)
    b = newSeq[float64](n)
    c = newSeq[float64](n)

  for i in 0..<n:
    (a[i], b[i], c[i]) = stdin.readLine.split.map(parseFloat).toTuple(3)

  proc check(x, y: float64): bool =
    for i in 0..<n:
      if a[i] * x + b[i] * y > c[i]: return false
    return true

  var ans: float64 = 0.0
  for i in 0..<n:
    for j in i+1..<n:
      if (a[i] * b[j] == a[j] * b[i]): continue
      let
        x = (c[i] * b[j] - c[j] * b[i]) / (a[i] * b[j] - a[j] * b[i])
        y = (c[i] * a[j] - c[j] * a[i]) / (b[i] * a[j] - b[j] * a[i])

      if check(x-Eps, y-Eps): ans.max = x + y

  print(ans)

when is_main_module:
  main()
