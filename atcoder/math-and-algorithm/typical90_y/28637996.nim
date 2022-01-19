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

proc f(x: int): int =
  result = 1
  if x == 0: result = 0; return
  var xx = x
  while xx > 0:
    result *= xx mod 10
    xx = xx div 10


proc main() =
  let n, b = read().parseInt()
  var fm = initHashSet[int]()
  proc dfs(dig, num: int) =
    if dig == 11:
      fm.incl(f(num))
      return

    for i in num mod 10..9:
      dfs(dig + 1, 10 * num + i)

  dfs(0, 0)
  var ans = 0
  for fmi in fm:
    let m = fmi + b
    if m - f(m) == b and m <= n: ans.inc

  print(ans)

when is_main_module:
  main()
