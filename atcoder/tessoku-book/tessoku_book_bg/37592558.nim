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

proc bit_ceil*(x: BiggestInt): int =
  if x < 0:
    return 0
  elif x <= 1:
    return x.int
  else:
    return 1 shl ((x - 1).fastLog2() + 1)

type SegTree = ref object
  n, leaf: int
  data: seq[int]

proc initSegTree*(n, v: int): SegTree =
  let leaf = bit_ceil(n)
  var data = newSeqWith(leaf * 2, 0)
  for i in leaf..<leaf + n:
    data[i] = v
  for i in countdown(n - 1, 1):
    data[i] = data[i * 2] + data[i * 2 + 1]

  return SegTree(n: n, leaf: leaf, data: data)

proc update*(self: var SegTree, index, v: int) =
  var i = index + self.leaf
  self.data[i] = v
  while i > 1:
    i = i shr 1
    self.data[i] = self.data[i * 2] + self.data[i * 2 + 1]

proc fold*(self: SegTree, l, r: var int): int =
  var
    lfold = 0
    rfold = 0
  l += self.leaf
  r += self.leaf

  while l < r:
    if l.testBit(0):
      lfold += self.data[l]
      l.inc
    if r.testBit(0):
      r.dec
      rfold += self.data[r]

    l = l shr 1
    r = r shr 1

  return lfold + rfold

proc main =
  let n, q = read(int)
  var seg = initSegTree(n, 0)
  q.times:
    let t = read(int)
    case t
    of 1:
      var pos, x = read(int)
      pos.dec
      seg.update(pos, x)
    of 2:
      var l, r = read(int)
      l.dec
      r.dec
      print(seg.fold(l, r))
    else:
      assert(false)


if isMainModule: main()
