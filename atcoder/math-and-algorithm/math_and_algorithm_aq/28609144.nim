{.warning[UnusedImport]: off.}
{.passc: "-I/opt/ac-library".}
# {.passc: "-I~/git/ac-library".}

import macros, strutils, sequtils, strformat, math, sugar, algorithm
proc powMod*(a, b, c: int): int {.importcpp: "atcoder::pow_mod(#, @)", header: "<atcoder/all>".}

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

proc main() =
  let (a, b) = getInts().toTuple(2)
  print(powMod(a, b, Mod))


when is_main_module:
  main()
