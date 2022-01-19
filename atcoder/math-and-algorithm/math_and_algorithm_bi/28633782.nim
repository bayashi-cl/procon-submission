{.warning[UnusedImport]: off.}
import macros, sugar
import math, bitops
import sequtils, strutils, strformat, algorithm
import sets, tables, deques


{.passc: "-I/opt/ac-library".}
# {.passc: "-I~/git/ac-library".}
proc powMod*(a, b, c: int): int {.importcpp: "atcoder::pow_mod(#, @)", header: "<atcoder/math>".}
proc invMod*(x, m: int): int {.importcpp: "atcoder::inv_mod(#, @)", header: "<atcoder/math>".}



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

proc binomCoef(n, m: int): seq[int] =
  var
    num = 1
    den = 1
  result = newSeq[int](n+1)
  result[0] = 1
  for i in 1..n:
    num *= n - i + 1
    num.mod = m
    den *= i
    den.mod = m
    result[i] = num * invMod(den, m) mod m


proc main() =
  let
    n = getInt()
    a = getInts()
    b = binomCoef(n-1, Mod)

  var ans = 0
  for i in 0..<n:
    ans += a[i] * b[i]
    ans.mod = Mod

  print(ans)

when is_main_module:
  main()
