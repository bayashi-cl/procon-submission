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
proc chmax*[T](a: var T; b: T): bool{.discardable.} = result = if a < b: a = b; true else: false
proc chmin*[T](a: var T; b: T): bool{.discardable.} = result = if a > b: a = b; true else: false
proc `|`*[T: SomeInteger](a, b: T): T = result = a or b
proc `&`*[T: SomeInteger](a, b: T): T = result = a and b
proc `%`*[T: SomeInteger](a, b: T): T = result = a mod b
proc `//`*[T: SomeInteger](a, b: T): T = result = a div b
proc `<<`*[T: SomeInteger](a, b: T): T = result = a shl b
proc `>>`*[T: SomeInteger](a, b: T): T = result = a shr b
proc `|=`*[T: SomeInteger](a: var T, b: T) = a = a or b
proc `&=`*[T: SomeInteger](a: var T, b: T) = a = a and b
proc `%=`*[T: SomeInteger](a: var T, b: T) = a = a mod b
proc `//=`*[T: SomeInteger](a: var T, b: T) = a = a div b
proc `<<=`*[T: SomeInteger](a: var T, b: T) = a = a shl b
proc `>>=`*[T: SomeInteger](a: var T, b: T) = a = a shr b
proc getInt*(): int = stdin.readLine.parseInt
proc getInts*(): seq[int] = stdin.readLine.split.map(parseInt)
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

proc bisect*(ok_val, ng_val: int, is_ok: proc(x: int): bool {.closure.}): int =
  var
    ok = ok_val
    ng = ng_val

  while abs(ok - ng) > 1:
    let mid = (ok + ng) // 2
    if is_ok(mid):
      ok = mid
    else:
      ng = mid
  return ok

proc bisect_float*(ok_val, ng_val: float, is_ok: proc(x: float): bool {.closure.}, rep: int = 100): float =
  var
    ok = ok_val
    ng = ng_val

  rep.times:
    let mid = (ok + ng) / 2
    if is_ok(mid):
      ok = mid
    else:
      ng = mid
  return ok

proc main() =
  let
    _ = getInt()
    a = getInts()

  proc mean(x: float): bool =
    # var dp = newSeqWith[n+1, @[0.0, 0.0]]
    var (p, q) = (0.0, 0.0)
    for ai in a:
      (p, q) = (q, max(p, q) + ai.toFloat() - x)
    return max(p, q) >= 0

  proc median(x: int): bool =
    var (p, q) = (0, 0)
    for ai in a:
      let c = if ai >= x: 1 else: -1
      (p, q) = (q, max(p, q) + c)

    return max(p, q) > 0

  print(bisect_float(0.0, Mod.toFloat(), mean))
  print(bisect(0, Mod, median))

when is_main_module:
  main()
