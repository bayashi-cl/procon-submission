static:
  when not defined(lazyCompile):
    template writeModule(path: string, code: untyped): untyped =
      discard staticExec("mkdir -p $(dirname " & path & ")")
      discard staticExec("cat - > " & path, astToStr(code))

    writeModule("byslib/core/intops.nim"):
      import math
      
      template `|`*(a, b: SomeInteger): untyped = a or b
      template `&`*(a, b: SomeInteger): untyped = a and b
      template `%`*(a, b: SomeInteger): untyped = floorMod(a, b)
      template `//`*(a, b: SomeInteger): untyped = floorDiv(a, b)
      template `<<`*(a, b: SomeInteger): untyped = a shl b
      template `>>`*(a, b: SomeInteger): untyped = a shr b
      
      template `|=`*(a, b: SomeInteger): untyped = a = a or b
      template `&=`*(a, b: SomeInteger): untyped = a = a and b
      template `%=`*(a, b: SomeInteger): untyped = a = floorMod(a, b)
      template `//=`*(a, b: SomeInteger): untyped = a = floorDiv(a, b)
      template `<<=`*(a, b: SomeInteger): untyped = a = a shl b
      template `>>=`*(a, b: SomeInteger): untyped = a = a shr b
      
      template `//+`*[T: SomeInteger](a, b: T): untyped = ceilDiv(a, b)
      

    writeModule("byslib/core/utils.nim"):
      template times*(n: int, body: untyped): untyped =
        for _ in 0..<n:
          body
      
      template tern*[T](cond: bool, t, f: T): auto =
        if cond: t
        else: f
      
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
      
      template proconDollars*[T](x: T): auto =
        when T is string or T is cstring:
          x
        elif compiles(x.join):
          x.join(" ")
        elif compiles(x.toSeq):
          x.toSeq.join(" ")
        else:
          $x
      
      template print*(args: varargs[string, proconDollars]) =
        stdout.write(args.join(" "))
        stdout.write('\n')
      
      when defined(release):
        template debug*(args: varargs[string, `$`]) = discard
      else:
        template debug*(args: varargs[string, `$`]) =
          let line = instantiationInfo().line
          stderr.write("📌 line" & align($line, 4) & ": ")
          stderr.write(args.join(" "))
          stderr.write('\n')
      

    writeModule("byslib/core/read.nim"):
      ## Input
      
      runnableExamples:
        let
          n = read(int)
          h, w = read(int) - 1
          c = readSeq(h, w, int)
          p = readSeq(n, tuple[x, y: int])
      
      import macros, strutils, sequtils
      
      let readNext* = iterator: string {.closure.} =
        while not stdin.endOfFile():
          for str in stdin.readLine.splitWhitespace():
            yield str
      
      template read*(tp: typedesc): auto =
        when tp is string:
          readNext()
        elif tp is char:
          readNext()[0]
        elif tp is int:
          readNext().parseInt()
        elif tp is float:
          readNext().parseFloat()
        elif tp is tuple:
          var result: tp
          for it in result.fields(): it = read(it.type)
          result
        elif tp is array:
          var result: tp
          for i in 0..result.high: result[i] = read(int)
          result
        else:
          doAssert: false
      
      template readSeq*(n: int; t: typedesc): auto = newSeqWith(n, read(t))
      template readSeq*(n, m: int; t: typedesc): auto = newSeqWith(n, newSeqWith(m, read(t)))
      

    writeModule("byslib/core/constant.nim"):
      const Mod* = 998244353
      const Mod7* = 1000000007
      
      template inf*(T): untyped =
        when T is SomeFloat: T(Inf)
        elif T is SomeInteger: T.high div 2
        else: assert(false)
      const IInf* = inf(int)
      

    writeModule("byslib/ntheory/modint.nim"):
      import std/[math, sugar, bitops, macros]
      
      type ModInt*[MOD: static[int]] = object of RootObj
        v: int
      
      template raw*(cls: typedesc[Modint], val: int): auto = cls(v: val)
      
      template norm*[T: ModInt](cls: typedesc[T], x: int or T): int =
        when x is T:
          x.val
        else:
          floorMod(x, cls.MOD)
      
      template initModInt*(val: int, modulo: static[int]): auto =
        type T = ModInt[modulo]
        T(v: T.norm(val))
      
      template genToModInt*(modulo: static[int]): auto =
        (val: int) => initModint(val, modulo)
      
      template `mod`*(self: ModInt): int = self.MOD
      template `val`*(self: ModInt): int = self.v
      template `$`*(self: ModInt): string = $self.val
      
      proc `^`*[T: ModInt](self: T, x: int): T =
        var q = abs(x)
        let minus = x < 0
        if q == 0: return T.raw(1)
      
        result = T.raw(1)
        var p = self
        for i in 0..q.fastLog2:
          if q.testBit(i): result *= p
          p *= p
      
        if minus: result = result.inv
      
      proc inv*[T: ModInt](self: T): T =
        result = self^(T.MOD - 2)
      
      proc `+=`*[T: Modint](self: var T, rhs: int or T) =
        self.v += T.norm(rhs)
        if self.v >= self.mod: self.v -= self.mod
      
      proc `-=`*[T: Modint](self: var T, rhs: int or T) =
        let rhs_v = T.norm(rhs)
        if rhs_v > self.v: self.v += self.mod
        self.v -= rhs_v
      
      proc `*=`*[T: Modint](self: var T, rhs: int or T) =
        self.v = T.norm(self.v * T.norm(rhs))
      
      template genBinOp(op, iop: untyped): untyped =
        proc op*[T: ModInt](lhs: T; rhs: int or T): T =
          result = lhs
          iop(result, rhs)
      
        proc op*[T: ModInt](lhs: int, rhs: T): T =
          result = T.raw(T.norm(lhs))
          iop(result, rhs)
      
      genBinOp(`+`, `+=`)
      genBinOp(`-`, `-=`)
      genBinOp(`*`, `*=`)
      
      template `div`*[T: ModInt](self: T, rhs: int or T): T =
        when rhs is ModInt:
          self * rhs.inv
        else:
          self * T.raw(T.norm(rhs)).inv
      
      template `//`*[T: ModInt](self: T, rhs: int or T): T = self div rhs
      template `//=`*[T: ModInt](self: var T, rhs: int or T) = self = self div rhs
      
      template `+`*[T: ModInt](self: T): T = self
      template `-`*[T: ModInt](self: T): T = T.raw(0) - self
      
      proc inc*[T: ModInt](self: var T) =
        self.v.inc
        if self.v == self.mod: self.v = 0
      proc dec*[T: ModInt](self: var T) =
        if self.v == 0: self.v = self.mod
        self.v.dec
      
      type
        ModInt998244353* = ModInt[998244353]
        ModInt1000000007* = ModInt[1000000007]
        Mint* = ModInt998244353
      
      let
        toModInt998244353* = genToModInt(998244353)
        toModInt1000000007* = genToModInt(1000000007)
        toMint* = toModInt998244353
      

    writeModule("byslib/core.nim"):
      {.warning[UnusedImport]: off.}
      import std/[
        macros, sugar, math, bitops,
        sequtils, strutils, strformat, algorithm,
        sets, tables, deques
      ]
      import core/[intops, utils, io, read, constant]
      

    type CompileError = object of CatchableError
    let resp = gorgeEx("nim cpp -d:lazyCompile -p:. -d:release --opt:speed --multimethods:on --warning[SmallLshouldNotBeUsed]:off --hints:off --out:a.out Main.nim")
    if resp.exitCode != 0:
      raise newException(CompileError, resp.output)
    quit(resp.exitCode)

include byslib/core

import byslib/ntheory/modint

proc main =
  let
    n = read(int)
    card = readSeq(n, tuple[a, b: int])
  var dp = newSeq[array[2, Mint]](n)
  dp[0] = [1.toMint, 1.toMint]

  for i in 1..<n:
    if card[i].a != card[i-1].a:
      dp[i][0] += dp[i-1][0]
    if card[i].a != card[i-1].b:
      dp[i][0] += dp[i-1][1]
    if card[i].b != card[i-1].a:
      dp[i][1] += dp[i-1][0]
    if card[i].b != card[i-1].b:
      dp[i][1] += dp[i-1][1]

  print((dp[^1][0].val + dp[^1][1].val) % Mod)

if isMainModule: main()
