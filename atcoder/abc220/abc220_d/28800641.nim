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
const mod9* = 998244353
const mod7* = 1000000007
const iInf* = int.high div 2
let read* = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s

proc main() =
  let
    n = getInt()
    a = getInts()

  var dp = newSeqWith(n, newSeq[int](10))
  dp[0][a[0]] = 1

  for i in 0..<n-1:
    for j in 0..<10:
      dp[i+1][(j + a[i+1]) % 10] += dp[i][j]
      dp[i+1][(j + a[i+1]) % 10] %= mod9
      dp[i+1][(j * a[i+1]) % 10] += dp[i][j]
      dp[i+1][(j * a[i+1]) % 10] %= mod9

  print(dp[n-1].join("\n"))

when is_main_module:
  main()
