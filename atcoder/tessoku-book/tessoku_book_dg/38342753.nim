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


## grundy

type Doubling = ref object
  db: seq[seq[int]]

proc initDoubling*(v: seq[int], queryType: typedesc[SomeInteger] = int): Doubling =
  let digits = sizeof(queryType) * 8
  var db = newSeqWith(digits, newSeq[int](v.len))
  db[0] = v
  for i in 0..<digits-1:
    for j in 0..v.high:
      db[i + 1][j] = db[i][db[i][j]]

  return Doubling(db: db)

proc query*(self: Doubling; src, x: int): int =
  result = src
  for i in 0..self.db.high:
    if x.testBit(i):
      result = self.db[i][result]

proc encode(a, b, c: int): int =
  return a * 9 + b * 3 + c

proc decode(x: int): (int, int, int) =
  let
    a = x // 9
    bc = x % 9
    b = bc // 3
    c = bc % 3

  return (a, b, c)

proc mex(a, b: int): int =
  for i in 0..2:
    if a != i and b != i:
      return i

  doAssert: false

proc main =
  let
    n, _, _ = read(int)
    a = readSeq(n, int)

  var nxt = newSeq[int](3^3)
  for i in 0..<3^3:
    let
      (p, q, r) = i.decode
      pp = mex(p, q)
      qq = mex(q, r)
      rr = mex(r, pp)

    nxt[i] = encode(pp, qq, rr)

  let dbl = nxt.initDoubling
  var nim = 0
  for ai in a:
    let
      d = ai // 3
      m = ai % 3

      (p, q, r) = dbl.query(encode(0, 0, 1), d).decode
      g = [p, q, r][m]

    nim = nim xor g

  if nim != 0:
    print("First")
  else:
    print("Second")

if isMainModule: main()
