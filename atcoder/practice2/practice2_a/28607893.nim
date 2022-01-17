{.passc: "-I/opt/ac-library".}
{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm

const aclDsu = "<atcoder/dsu>"

type
  Dsu {.header: aclDsu, importcpp: "atcoder::dsu".} = object

proc initDsu(n: int): Dsu{.header: aclDsu, importcpp: "atcoder::dsu(@)".}
proc merge(this: Dsu, a, b: int): int{.header: aclDsu, importcpp: "#.merge(@)", discardable.}
proc same(this: Dsu, a, b: int): bool{.header: aclDsu, importcpp: "#.same(@)".}
# proc leader(this: Dsu, a: int): int{.header: aclDsu, importcpp: "#.leader(@)".}
# proc size(this: Dsu, a: int): int{.header: aclDsu, importcpp: "#.size(@)".}


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

proc main() =
  let (n, q) = getInts().toTuple(2)
  var uft = initDsu(n)
  q.times:
    let (t, u, v) = getInts().toTuple(3)
    if t == 0:
      uft.merge(u, v)
    else:
      if uft.same(u, v):
        print(1)
      else:
        print(0)


when is_main_module:
  main()
