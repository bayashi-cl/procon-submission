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

proc matMul(a, b: seq[seq[SomeFloat]]): seq[seq[SomeFloat]] =
  assert a[0].len() == b.len()
  let
    r = a.len()
    c = a[0].len()
    d = b[0].len()

  result = newSeqWith(r, newSeq[float64](d))
  for i in 0..<r:
    for j in 0..<d:
      for k in 0..<c:
        result[i][j] += a[i][k] * b[k][j]


proc pow(mat: seq[seq[SomeFloat]], p: int): seq[seq[SomeFloat]] =
  let n = mat.len()
  var base = mat
  result = newSeqWith(n, newSeq[float64](n))
  for i in 0..<n: result[i][i] = 1

  for d in 0..fastLog2(p):
    if p.testBit(d):
      result = matMul(result, base)
    base = matMul(base, base)

proc main() =
  let
    x, y, z, tf = read().parseFloat()
    t = tf.toInt()
    mat: seq[seq[float64]] = @[@[1-x, y, 0.0], @[0.0, 1-y, z], @[x, 0.0, 1-z]]
    res = mat.pow(t)

  var ans = newSeq[float64](3)
  for i in 0..<3: ans[i] = res[i].sum()
  print(ans)


when is_main_module:
  let q = getInt()
  q.times: main()
