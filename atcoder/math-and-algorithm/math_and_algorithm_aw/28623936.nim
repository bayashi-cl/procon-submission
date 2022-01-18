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
let read* = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s

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


proc pow*(mat: seq[seq[int]], p: int, m: int = 1000000007): seq[seq[int]] =
  let n = mat.len()
  var base = mat
  result = newSeqWith(n, newSeq[int](n))
  for i in 0..<n: result[i][i] = 1

  for d in 0..fastLog2(p):
    if p.testBit(d):
      result = matMul(result, base, m)
    base = matMul(base, base, m)

proc main() =
  let k, n = read().parseInt()
  var verticalPut = newSeqWith(1 shl k, newSeq[int]())
  const domino = 3 # 0b0011
  for s in 0..<(1 shl k):
    verticalPut[s].add(s)
    for d in 0..k-2:
      let domino_s = domino shl d
      if (s and domino_s) == 0:
        verticalPut[s].add(s or domino_s)
  if k == 4:
    verticalPut[0].add(15) # 0b1111

  var mat = newSeqWith(1 shl k, newSeq[int](1 shl k))
  let mx = (1 shl k) - 1
  for f in 0..<(1 shl k):
    let nxt = f xor mx
    for nxt_state in verticalPut[nxt]:
      mat[f][nxt_state] = 1

  let ans_mat = mat.pow(n, Mod)
  print(ans_mat[mx][mx])

when is_main_module:
  main()
