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

proc main =
  let
    h, w = read(int)
    a = readSeq(h, w, int)

  proc flip(i, j: int, f: bool): int =
    result = a[i][j]
    if f: result = 1 - result

  proc iso(i, j: int, x, y, z: bool): bool =
    let c = flip(i, j, y)
    var l, r, u, d = -1
    if i - 1 >= 0: u = flip(i - 1, j, x)
    if i + 1 < h: d = flip(i + 1, j, z)
    if j - 1 >= 0: l = flip(i, j - 1, y)
    if j + 1 < w: r = flip(i, j + 1, y)

    return c != l and c != r and c != u and c != d

  var dp = newSeqWith(h + 1, newSeqWith(2, newSeqWith(2, IInf.int)))
  dp[0] = @[@[0, 0], @[1, 1]]
  for i in 1..h:
    for prev in 0..1:
      for now in 0..1:
        for next in 0..1:
          var able = true
          for j in 0..<w:
            if iso(i - 1, j, prev == 1, now == 1, next == 1):
              able = false
              break

          if able:
            dp[i][next][now].chmin(dp[i - 1][now][prev] + next.int32)

  var ans: int = IInf
  for i in 0..1:
    for j in 0..1:
      ans.chmin(dp[h][i][j])

  if ans == IInf: ans = -1
  print(ans)

if isMainModule: main()