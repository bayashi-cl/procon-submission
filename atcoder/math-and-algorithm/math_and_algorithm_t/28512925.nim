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

proc main() =
  let n = getInt()
  var v = getInts()
  v.sort()
  var ans = 0
  for a in 0..<n:
    for b in a+1..<n:
      if v[a] + v[b] > 1000:
        break
      for c in b+1..<n:
        if v[a] + v[b] + v[c] > 1000:
          break
        for d in c+1..<n:
          if v[a] + v[b] + v[c] + v[d] > 1000:
            break
          for e in d+1..<n:
            let s = v[a] + v[b] + v[c] + v[d] + v[e]
            if s > 1000:
              break
            elif s == 1000:
              ans = ans + 1
  echo ans

when is_main_module:
  main()
