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

type MultiComb = object
  fact, factinv, inv: seq[int]
  m: int

proc initMultiComb*(n, m: int): MultiComb =
  result = MultiComb(fact: newSeq[int](n+1), factinv: newSeq[int](n+1), inv: newSeq[int](n+1), m: m)
  result.fact[0] = 1
  result.fact[1] = 1
  result.factinv[0] = 1
  result.factinv[1] = 1
  result.inv[1] = 1
  for i in 2..n:
    result.fact[i] = result.fact[i - 1] * i mod m
    result.inv[i] = m - result.inv[m mod i] * (m div i) mod m
    result.factinv[i] = result.factinv[i - 1] * result.inv[i] mod m

proc comb(self: MultiComb, n, r: int): int =
  if r < 0 or n < r:
    result = 0
  else:
    result = self.fact[n] * (self.factinv[r] * self.factinv[n - r] mod self.m) mod self.m

proc ceilDiv*[T: SomeInteger](x, y: T): T {.inline.} =
  result = x div y
  if not (x < 0 xor y < 0) and x mod y != 0:
    inc result

proc main() =
  let n = getInt()
  let mc = initMultiComb(n, Mod)
  for k in 1..n:
    var ans = 0
    for a in 1..ceilDiv(n, k):
      ans += mc.comb(n - (k - 1) * (a - 1), a)
      ans.mod = Mod
    print(ans)

when is_main_module:
  main()
