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
proc print[Ty](args: varargs[Ty, `$`]) =
  stdout.write(args.join(" "))
  stdout.write("\n")

type CumSum = ref object
  data: seq[int]
  build: bool

proc setval*(self: CumSum, p, v: int) =
  assert(not self.build, "already build")
  self.data[p+1] = v

proc construct*(self: CumSum) =
  assert(not self.build, "already build")
  let n = self.data.len()
  for i in 1..<n:
    self.data[i] += self.data[i-1]
  self.build = true

proc toCumSum*(v: openArray[int]): CumSum =
  let n = v.len()
  result = CumSum(data: newSeq[int](n+1), build: false)
  for i, vi in v:
    result.setval(i, vi)
  result.construct()

proc initCumSum*(n: int): CumSum =
  result = CumSum(data: newSeq[int](n+1), build: false)

proc sum*(self: CumSum, l, r: int): int =
  assert(self.build, "need construct")
  if l > r:
    return 0
  else:
    return self.data[r] - self.data[l]


proc main() =
  let
    (_, q) = getInts().toTuple(2)
    cs = getInts().toCumSum()
  for i in 0..<q:
    let (l, r) = getInts().toTuple(2)
    print(cs.sum(l-1, r))

when is_main_module:
  main()
