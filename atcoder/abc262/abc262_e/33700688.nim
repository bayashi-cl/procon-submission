static:
  when not defined(lazyCompile):
    template writeModule(path: string, code: untyped): untyped =
      discard staticExec("mkdir -p $(dirname " & path & ")")
      discard staticExec("cat - > " & path, astToStr(code))

    writeModule("byslib/core/intops.nim"):
      template `|`*(a, b: SomeInteger): untyped = a or b
      template `&`*(a, b: SomeInteger): untyped = a and b
      template `%`*(a, b: SomeInteger): untyped = a mod b
      template `//`*(a, b: SomeInteger): untyped = a div b
      template `<<`*(a, b: SomeInteger): untyped = a shl b
      template `>>`*(a, b: SomeInteger): untyped = a shr b
      
      template `|=`*(a, b: SomeInteger): untyped = a = a or b
      template `&=`*(a, b: SomeInteger): untyped = a = a and b
      template `%=`*(a, b: SomeInteger): untyped = a = a mod b
      template `//=`*(a, b: SomeInteger): untyped = a = a div b
      template `<<=`*(a, b: SomeInteger): untyped = a = a shl b
      template `>>=`*(a, b: SomeInteger): untyped = a = a shr b
      
      template `//+`*[T: SomeInteger](a, b: T): untyped =
        if (a < 0) xor (b < 0):
          a div b
        else:
          if a < 0:
            (a + b + 1) div b
          else:
            (a + b - 1) div b
      
      template `//-`*[T: SomeInteger](a, b: T): untyped =
        if (a < 0) xor (b < 0):
          if a < 0:
            (a - b + 1) div b
          else:
            (a - b - 1) div b
        else:
          a div b
      

    writeModule("byslib/core/utils.nim"):
      template irange*(stop: SomeInteger): untyped = 0..<stop
      template irange*(start, stop: SomeInteger): untyped = start..<stop
      template times*(n: int, body: untyped): untyped =
        for _ in 0..<n:
          body
      
      proc chmax*[T](a: var T; b: T): bool {.discardable.} =
        if a < b:
          a = b
          result = true
        else:
          result = false
      
      proc chmin*[T](a: var T; b: T): bool {.discardable.} =
        if a > b:
          a = b
          result = true
        else:
          result = false
      

    writeModule("byslib/core/io.nim"):
      import macros, strutils, sequtils
      
      proc print*(args: varargs[string, `$`]) =
        # 要検討
        stdout.write(args.join(" "))
        stdout.write('\n')
      
      proc debug*(args: varargs[string, `$`]) =
        # 要検討
        stderr.write(args.join(" "))
        stderr.write('\n')
      
      let readNext* = iterator(getChar: bool = false): string {.closure.} =
        while not stdin.endOfFile():
          for bufStr in stdin.readLine.splitWhitespace():
            block remainingBuf:
              var cursor = 0
              let bufSize = bufStr.len
      
              while getChar:
                yield bufStr[cursor..cursor]
                cursor.inc
                if cursor == bufSize:
                  break remainingBuf
              if cursor == 0:
                yield bufStr
              else:
                yield bufStr[cursor..bufStr.high]
      
      template read*(t: typedesc[string]): string = readNext()
      template read*(t: typedesc[char]): char = readNext(true)[0]
      template read*(t: typedesc[int]): t = readNext().parseInt()
      template read*(t: typedesc[float]): t = readNext().parseFloat()
      proc read*(t: typedesc[tuple]): t =
        for it in result.fields():
          it = read(it.type)
      proc read*(n: static[int], t: typedesc): array[n, t] =
        for i in 0..<n:
          result[i] = read(t)
      template readSeq*(n: int, t: typedesc): seq[t] =
        newSeqWith(n, read(t))
      template readSeq*(n, m: int, t: typedesc): seq[seq[t]] =
        newSeqWith(n, newSeqWith(m, read(t)))
      

    writeModule("byslib/core/constant.nim"):
      const Mod* = 998244353
      const Mod7* = 1000000007
      
      template inf*(T): untyped =
        when T is SomeFloat: T(Inf)
        elif T is SomeInteger: T.high div 2
        else: assert(false)
      const IInf* = inf(int32)
      const LInf* = inf(BiggestInt)
      

    writeModule("byslib/core.nim"):
      {.warning[UnusedImport]: off.}
      import std/[
        macros, sugar, math, bitops,
        sequtils, strutils, strformat, algorithm,
        sets, tables, deques
      ]
      import core/[intops, utils, io, constant]
      

    type CompileError = object of CatchableError
    let resp = gorgeEx("nim cpp -d:lazyCompile -p:. -d:release --opt:speed --multimethods:on --warning[SmallLshouldNotBeUsed]:off --hints:off --out:a.out Main.nim")
    if resp.exitCode != 0:
      raise newException(CompileError, resp.output)
    quit(resp.exitCode)

include byslib/core

template countIt*(s, pred: untyped): int =
  var result = 0
  for it {.inject.} in s:
    if pred: result += 1
  result

type ModComb* = ref object
  modulo: int
  fact, inv, invFact: seq[int]

proc extend*(self: var ModComb, n: int) =
  for i in self.fact.len..n:
    self.fact.add(self.fact[^1] * i mod self.modulo)
    self.inv.add(self.modulo - self.inv[self.modulo mod i] * (self.modulo div i) mod self.modulo)
    self.invFact.add((self.invFact[^1] * self.inv[^1]) mod self.modulo)

proc comb*(mc: var ModComb, n, r: int): int =
  if r < 0 or n < r:
    return 0
  else:
    mc.extend(n)
    return mc.fact[n] * (mc.invFact[r] * mc.invFact[n - r] mod mc.modulo) mod mc.modulo

proc initModComb*(n: int = 1, modulo: int = 998244353): ModComb =
  result = ModComb(modulo: modulo, fact: @[1, 1], inv: @[0, 1], invFact: @[1, 1])
  result.extend(n)

proc main =
  let n, m, k = read(int)
  var
    cnt = newSeq[int](n)
    mc = initModComb()

  m.times:
    let u, v = read(int) - 1
    cnt[u].inc
    cnt[v].inc
  let
    odd = cnt.countIt(it % 2 == 1)
    even = n - odd

  var ans = 0
  for i in countup(0, min(k, odd), 2):
    if k - i <= even:
      ans += mc.comb(odd, i) * mc.comb(even, k - i)
      ans %= Mod

  ans.print





if isMainModule: main()
