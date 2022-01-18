{.warning[UnusedImport]: off.}
# {.passc: "-I/opt/ac-library".}
# {.passc: "-I~/git/ac-library".}
# proc powMod*(a, b, c: int): int {.importcpp: "atcoder::pow_mod(#, @)", header: "<atcoder/all>".}

import macros, strutils, sequtils, strformat, math, sugar, algorithm, bitops
let read* = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s
macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
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

proc powMod(a, b, m: int): int =
  result = 1
  var p = a
  for d in 0..fastLog2(b):
    if b.testBit(d):
      result *= p
      result = result mod m
    p = (p^2) mod m

proc main() =
  let a, b = read().parseInt()
  print(a.powMod(b, Mod))


when is_main_module:
  main()
