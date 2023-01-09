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
      

    writeModule("byslib/backport/sequtilsBp.nim"):
      ## This module is backport of sequtils
      ## https://github.com/nim-lang/Nim/blob/devel/lib/pure/collections/sequtils.nim
      ## Copyright (C) 2006-2021 Andreas Rumpf. All rights reserved.
      ## https://opensource.org/licenses/mit-license.php
      
      func minIndex*[T](s: openArray[T]): int =
        ## Returns the index of the minimum value of `s`.
        ## `T` needs to have a `<` operator.
        runnableExamples:
          let
            a = @[1, 2, 3, 4]
            b = @[6, 5, 4, 3]
            c = [2, -7, 8, -5]
            d = "ziggy"
          assert minIndex(a) == 0
          assert minIndex(b) == 3
          assert minIndex(c) == 1
          assert minIndex(d) == 2
      
        for i in 1..high(s):
          if s[i] < s[result]: result = i
      
      func maxIndex*[T](s: openArray[T]): int =
        ## Returns the index of the maximum value of `s`.
        ## `T` needs to have a `<` operator.
        runnableExamples:
          let
            a = @[1, 2, 3, 4]
            b = @[6, 5, 4, 3]
            c = [2, -7, 8, -5]
            d = "ziggy"
          assert maxIndex(a) == 3
          assert maxIndex(b) == 0
          assert maxIndex(c) == 2
          assert maxIndex(d) == 0
      
        for i in 1..high(s):
          if s[i] > s[result]: result = i
      
      proc unzip*[S, T](s: openArray[(S, T)]): (seq[S], seq[T]) =
        ## Returns a tuple of two sequences split out from a sequence of 2-field tuples.
        runnableExamples:
          let
            zipped = @[(1, 'a'), (2, 'b'), (3, 'c')]
            unzipped1 = @[1, 2, 3]
            unzipped2 = @['a', 'b', 'c']
          assert zipped.unzip() == (unzipped1, unzipped2)
          assert zip(unzipped1, unzipped2).unzip() == (unzipped1, unzipped2)
        result[0] = newSeq[S](s.len)
        result[1] = newSeq[T](s.len)
        for i in 0..<s.len:
          result[0][i] = s[i][0]
          result[1][i] = s[i][1]
      
      template countIt*(s: openArray, pred: untyped): int =
        ## Returns a count of all the items that fulfill the predicate.
        ##
        ## The predicate needs to be an expression using
        ## the `it` variable for testing, like: `countIt(@[1, 2, 3], it > 2)`.
        ##
        runnableExamples:
          let numbers = @[-3, -2, -1, 0, 1, 2, 3, 4, 5, 6]
          iterator iota(n: int): int =
            for i in 0..<n: yield i
          assert numbers.countIt(it < 0) == 3
          assert countIt(iota(10), it < 2) == 2
      
        var result = 0
        for it {.inject.} in s:
          if pred: result += 1
        result
      

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
import byslib/backport/sequtilsBp

proc main =
  let t = read(int)
  t.times:
    let
      n = read(int)
      a = readSeq(n, int)

    print a.countIt(it % 2 == 1)


if isMainModule: main()
