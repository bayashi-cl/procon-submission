{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, sets

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
proc getInt(): int {.used.} = stdin.readLine.parseInt
proc getInts(): seq[int] {.used.} = stdin.readLine.split.map(parseInt)

proc main() =
  let
    (_, s) = getInts().toTuple(2)
    a = getInts()

  var sum = toHashSet([0])
  for ai in a:
    var addn = newSeq[int]()
    for si in sum:
      if si + ai == s:
        echo "Yes"
        return
      elif si + ai < s:
        addn.add(si + ai)
    for e in addn:
      sum.incl(e)

  echo "No"

when is_main_module:
  main()
