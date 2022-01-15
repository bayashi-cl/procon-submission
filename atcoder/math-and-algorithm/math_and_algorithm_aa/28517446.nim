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

proc mergeSort(s: seq[int]): seq[int] =
  let
    n = s.len()
    m = n div 2

  if n == 1:
    return s

  var
    left = mergeSort(s[0..<m])
    right = mergeSort(s[m..<n])

  left.reverse()
  right.reverse()

  result = newSeq[int]()
  while len(left) != 0 and len(right) != 0:
    if left[left.high] <= right[right.high]:
      result.add(left.pop())
    else:
      result.add(right.pop())

  if left.len() > 0:
    left.reverse()
    result = result.concat(left)
  if right.len() > 0:
    right.reverse()
    result = result.concat(right)



proc main() =
  let _ = getInt()
  var a = getInts()
  echo mergeSort(a).join(" ")

when is_main_module:
  main()
