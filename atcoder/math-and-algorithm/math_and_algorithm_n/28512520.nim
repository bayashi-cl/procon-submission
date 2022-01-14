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

proc prime_factorize(n: var int): seq[int] =
  result = newSeq[int]()
  while (n and 1) == 0:
    result.add(2)
    n = n shr 1

  var f = 3
  while f^2 <= n:
    if n mod f == 0:
      result.add(f)
      n = n div f
    else:
      f += 2
  if n != 1:
    result.add(n)

proc main() =
  var n = getInt()
  echo prime_factorize(n).join(" ")

when is_main_module:
  main()
