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
      

    writeModule("byslib/ds/unionfind.nim"):
      import sequtils
      
      type UnionFindTree* = ref object
        parent_or_size: seq[int]
      
      proc find*(self: var UnionFindTree, x: int): int =
        if self.parent_or_size[x] < 0:
          return x
        else:
          result = self.find(self.parent_or_size[x])
          self.parent_or_size[x] = result
      
      # proc find*(self: var UnionFindTree, x: int): int =
      #   result = x
      #   if self.parent_or_size[result] >= 0:
      #     var path = newSeq[int]()
      #     while self.parent_or_size[result] >= 0:
      #       path.add(result)
      #       result = self.parent_or_size[result]
      
      #     for p in path:
      #       self.parent_or_size[p] = result
      
      proc same*(self: var UnionFindTree, a, b: int): bool =
        return self.find(a) == self.find(b)
      
      proc union*(self: var UnionFindTree, a, b: int): int {.discardable.} =
        var
          a_leader = self.find(a)
          b_leader = self.find(b)
      
        if a_leader == b_leader: return a_leader
      
        if self.parent_or_size[a_leader] > self.parent_or_size[b_leader]:
          swap(a_leader, b_leader)
      
        self.parent_or_size[a_leader] += self.parent_or_size[b_leader]
        self.parent_or_size[b_leader] = a_leader
      
        return a_leader
      
      proc initUnionFindTree*(n: int): UnionFindTree =
        result = UnionFindTree(parent_or_size: newSeqWith(n, -1))
      

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
import byslib/ds/unionfind

proc main =
  let n, m = read(int)
  var
    uf = initUnionFindTree(n)
    ans = n

  m.times:
    let u, v = read(int) - 1
    if not uf.same(u, v): ans.dec
    uf.union(u, v)

  print ans

if isMainModule: main()
