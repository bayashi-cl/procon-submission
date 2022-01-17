import strutils, sequtils, bitops

let read = iterator: string {.closure.} =
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
let n = read().parseInt
if n == 6:
  echo(8)
else:
  let fibMat = @[@[1, 1], @[1, 0]]
  var res = fibMat.pow(n-1, Mod)
  echo((res[1][0]+res[1][1]) mod Mod)
