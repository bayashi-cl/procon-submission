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

proc factorial(n: int): int =
  if n == 1:
    return 1
  else:
    return n * factorial(n - 1)

proc main() =
  let n = getInt()
  echo factorial(n)
  # echo fac(n)

when is_main_module:
  main()
