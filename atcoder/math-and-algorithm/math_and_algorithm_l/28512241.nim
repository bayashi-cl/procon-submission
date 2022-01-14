{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar

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

proc is_prime(n: int): bool =
  if n <= 1:
    return false
  if (n and 1) == 0:
    return false

  for p in countup(3, isqrt(n), 2):
    if n mod p == 0:
      return false

  return true

proc main() =
  let n = getInt()
  if is_prime(n):
    echo "Yes"
  else:
    echo "No"

when is_main_module:
  main()
