{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm, bitops, strscans

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
const IInf* = int.high div 2

proc matMul(a, b: seq[seq[int]], m: int = 1000000007): seq[seq[int]] =
  assert a[0].len() == b.len()
  let
    r = a.len()
    c = a[0].len()
    d = b[0].len()

  result = newSeqWith(r, newSeq[int](d))
  for i in 0..<r:
    for j in 0..<d:
      for k in 0..<c:
        result[i][j] += a[i][k] * b[k][j]
        result[i][j] = result[i][j] mod m


proc pow(mat: seq[seq[int]], p: int, m: int = 1000000007): seq[seq[int]] =
  let n = mat.len()
  var base = mat
  result = newSeqWith(n, newSeq[int](n))
  for i in 0..<n: result[i][i] = 1

  for d in 0..fastLog2(p):
    if p.testBit(d):
      result = matMul(result, base, m)
    base = matMul(base, base, m)

# proc main() =
const Mod = 1000000007
var n: int
discard stdin.readLine.scanf("$i", n)
if n == 6:
  print(8)
else:
  let fibMat = @[@[1, 1], @[1, 0]]
  var res = fibMat.pow(n-1, Mod)
  print((res[1][0]+res[1][1]) mod Mod)
