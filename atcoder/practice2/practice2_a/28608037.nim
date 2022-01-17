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

type
  Dsu = ref object
    n: int
    parent_or_size: seq[int]

proc initDsu(n: int): Dsu =
  return Dsu(n: n, parent_or_size: newSeqWith(n, -1))

proc leader(self: Dsu; a: int): int {.inline.} =
  if self.parent_or_size[a] < 0:
    return a
  self.parent_or_size[a] = self.leader(self.parent_or_size[a])
  return self.parent_or_size[a]

proc same(self: Dsu; a, b: int): bool {.inline.} =
  self.leader(a) == self.leader(b)

proc merge(self: Dsu; a, b: int): int {.inline, discardable.} =
  var
    x = self.leader(a)
    y = self.leader(b)

  if x == y: return x
  if -self.parent_or_size[x] < -self.parent_or_size[y]:
    swap(x, y)
  self.parent_or_size[x] += self.parent_or_size[y]
  self.parent_or_size[y] = x
  return x


proc main() =
  let (n, q) = getInts().toTuple(2)
  var uft = initDsu(n)
  q.times:
    let (t, u, v) = getInts().toTuple(3)
    if t == 0:
      uft.merge(u, v)
    else:
      if uft.same(u, v):
        print(1)
      else:
        print(0)

when is_main_module:
  main()
