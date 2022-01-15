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
  let
    (a, b, h, m) = stdin.readLine.split.map(parseFloat).toTuple(4)

    m_theta = PI / 2.0 - m * TAU / 60.0
    h_theta = PI / 2.0 - (h*60.0+m) * TAU / (60.0*12.0)

    hx = a * cos(h_theta)
    hy = a * sin(h_theta)
    mx = b * cos(m_theta)
    my = b * sin(m_theta)

  echo hypot(hx-mx, hy-my)

when is_main_module:
  main()
