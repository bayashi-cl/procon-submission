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

proc main() =
  const a = @[1, 1, 1, 2, 1, 2, 1, 5, 2, 2, 1, 5, 1, 2, 1, 14, 1, 5, 1, 5, 2, 2, 1, 15, 2, 2, 5, 4, 1, 4, 1, 51]
  let k = getInt() - 1
  print(a[k])

when is_main_module:
  main()
