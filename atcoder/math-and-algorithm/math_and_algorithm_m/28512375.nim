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

func isqrt(x: int): int =
  result = 0
  var q = 1

  while q <= x:
    q = q shl 2

  var z = x
  while q > 1:
    q = q shr 2
    let t = z - result - q
    result = result shr 1
    if t >= 0:
      z = t
      result += q

proc divisor(n: int): seq[int] =
  var
    lower = newSeq[int]()
    upper = newSeq[int]()

  for d in 1..isqrt(n):
    if n mod d == 0:
      lower.add(d)
      if d * d != n:
        upper.add(n div d)

  upper.reverse()
  return lower.concat(upper)

proc main() =
  let n = getInt()
  echo divisor(n).join("\n")

when is_main_module:
  main()
