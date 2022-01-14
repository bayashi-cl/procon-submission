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

type Osa_K = ref object
  mx: int
  spf: seq[int]

proc sieve(self: Osa_K) =
  for i in countup(2, self.mx, 2):
    self.spf[i] = 2
  for p in countup(3, isqrt(self.mx), 2):
    if self.spf[p] != p:
      continue
    for k in countup(p ^ 2, self.mx, p):
      if self.spf[k] == k:
        self.spf[k] = p

func is_prime(self: Osa_K, n: int): bool =
  if n <= 1:
    return false
  return self.spf[n] == n

proc initOsa_K(n: int): Osa_K =
  var cls = Osa_K(mx: n, spf: toSeq(0..n))
  cls.sieve()
  return cls

proc main() =
  let n = getInt()
  var
    osa_k = initOsa_K(n)
    ans = newSeq[int]()

  for i in 2..n:
    if osa_k.is_prime(i):
      ans.add(i)

  echo ans.join(" ")

when is_main_module:
  main()
