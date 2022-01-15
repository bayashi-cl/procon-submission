{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
proc getInt(): int {.used.} = stdin.readLine.parseInt
proc getInts(): seq[int] {.used.} = stdin.readLine.split.map(parseInt)
proc print*[Ty](args: varargs[Ty, `$`], sep: string = " ") =
  var s = args.join(sep)
  s.add('\n')
  stdout.write(s)
proc debug*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stderr.write(s)

proc main() =
  let
    t = getInt()
    n = getInt()
  var imos = newSeq[int](t+1)
  n.times:
    let (l, r) = getInts().toTuple(2)
    imos[l].inc()
    imos[r].dec()
  imos.cumsum()
  print(imos[0..<imos.high].join("\n"))

when is_main_module:
  main()
