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
proc print*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stdout.write(s)
proc debug*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stderr.write(s)

proc main() =
  let n = getInt()
  var
    a = getInts()
    cs = newSeq[int](n)
  for i in 1..<n:
    cs[i] = a[i-1]
  cs.cumsum()

  let m = getInt()
  var
    ans = 0
    b = getInt()
  b.dec()

  (m-1).times():
    var bi = getInt()
    bi.dec()
    ans += abs(cs[bi] - cs[b])
    b = bi

  print(ans)


when is_main_module:
  main()
