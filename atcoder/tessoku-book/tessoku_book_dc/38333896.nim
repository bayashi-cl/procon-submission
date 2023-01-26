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
      template readSeq*(n, m: int, t: typedesc): auto =
        newSeqWith(n, newSeqWith(m, read(t)))
      

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
      
      template genBinOp(op, iop: untyped): untyped =
        proc op*[T: ModInt](lhs: T; rhs: int or T): T =
          result = lhs
          iop(result, rhs)
      
        proc op*[T: ModInt](lhs: int, rhs: T): T =
          result = T.raw(T.norm(lhs))
          iop(result, rhs)
      
      
      proc `+=`*[T: Modint](self: var T, rhs: int or T) =
        self.v += T.norm(rhs)
        if self.v >= self.mod: self.v -= self.mod
      
      genBinOp(`+`, `+=`)
      
      proc `-=`*[T: Modint](self: var T, rhs: int or T) =
        let rhs_v = T.norm(rhs)
        if rhs_v > self.v: self.v += self.mod
        self.v -= rhs_v
      
      genBinOp(`-`, `-=`)
      
      proc `*=`*[T: Modint](self: var T, rhs: int or T) =
        self.v = T.norm(self.v * T.norm(rhs))
      
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
      import core/[intops, utils, io, constant]
      

    type CompileError = object of CatchableError
    let resp = gorgeEx("nim cpp -d:lazyCompile -p:. -d:release --opt:speed --multimethods:on --warning[SmallLshouldNotBeUsed]:off --hints:off --out:a.out Main.nim")
    if resp.exitCode != 0:
      raise newException(CompileError, resp.output)
    quit(resp.exitCode)

include byslib/core
import byslib/ntheory/modint


proc comb(n, r: int; modulo: static[int] = 998244353): ModInt[modulo] =
  var num, den = initModInt(1, modulo)
  for i in 0..<r:
    num *= n - i
    den *= i + 1

  return num // den

proc main =
  let h, w = read(int)
  print(comb(h + w - 2, h - 1, 1000000007))


if isMainModule: main()
