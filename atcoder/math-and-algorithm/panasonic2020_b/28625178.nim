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

proc robustCeilDiv*[T: SomeInteger](x, y: T): T {.inline.} =
  ## Ceil division is conceptually defined as `ceil(x / y)`.
  ##
  ## This is different from the `system.div` operator in stdlib,
  ## which is defined as `trunc(x / y)`.
  ## That is, `div` rounds towards `0` and `ceilDiv` rounds up.
  runnableExamples:
    assert robustCeilDiv(12, 3) == 4
    assert robustCeilDiv(13, 3) == 5
    assert robustCeilDiv(-13, 3) == -4
    assert robustCeilDiv(13, -3) == -4
    assert robustCeilDiv(-13, -3) == 5

  result = x div y
  if not (x < 0 xor y < 0) and x mod y != 0:
    inc result

proc main() =
  let h, w = read().parseInt()
  if h == 1 or w == 1:
    print(1)
  else:
    if w mod 2 == 0:
      print(w div 2 * h)
    elif h mod 2 == 0:
      print(h div 2 * w)
    else:
      let ans = robustceilDiv(h, 2) * robustCeilDiv(w, 2) + (h div 2) * (w div 2)
      print(ans)

when is_main_module:
  main()
