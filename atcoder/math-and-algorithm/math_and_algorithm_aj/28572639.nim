{.warning[UnusedImport]: off.}
import macros, strutils, sequtils, strformat, math, sugar, algorithm

macro toTuple*(arr: auto, cnt: static[int]): auto =
  let t = genSym()
  result = quote do:
    (let `t` = `arr`; ())
  for i in 0..<cnt:
    result[1].add(quote do: `t`[`i`])
template times*(n: int, body: untyped): untyped = (for _ in 0..<n: body)
proc getInt*(): int = stdin.readLine.parseInt
proc getInts*(): seq[int] = stdin.readLine.split.map(parseInt)
proc print*[Ty](args: varargs[Ty, `$`]) =
  var s = args.join(" ")
  s.add('\n')
  stdout.write(s)

proc main() =
  let (n, q) = getInts().toTuple(2)
  var imos = newSeq[int](n+1)
  q.times:
    let (l, r, x) = getInts().toTuple(3)
    imos[l-1] += x
    imos[r] -= x

  imos.cumsum()
  var ans = ""
  for i in 0..<n-1:
    if imos[i] > imos[i+1]:
      ans.add('>')
    elif imos[i] == imos[i+1]:
      ans.add('=')
    else:
      ans.add('<')
  print(ans)


when is_main_module:
  main()
