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
      
      template read*[T](_: typedesc[T]): T =
        when T is string:
          readNext()
        elif T is char:
          readNext()[0]
        elif T is int:
          readNext().parseInt()
        elif T is float:
          readNext().parseFloat()
        elif T is tuple:
          var result: T
          for it in result.fields(): it = read(it.type)
          result
        elif T is array:
          var result: T
          for i in result.low..result.high: result[i] = read(int)
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
      
      proc same*(self: var UnionFindTree, a, b: int): bool =
        return self.find(a) == self.find(b)
      
      proc union*(self: var UnionFindTree, a, b: int): tuple[mearge: bool, leader: int] {.discardable.} =
        var
          a_leader = self.find(a)
          b_leader = self.find(b)
      
        if a_leader == b_leader: return (mearge: false, leader: a_leader)
      
        if self.parent_or_size[a_leader] > self.parent_or_size[b_leader]:
          swap(a_leader, b_leader)
      
        self.parent_or_size[a_leader] += self.parent_or_size[b_leader]
        self.parent_or_size[b_leader] = a_leader
      
        return (mearge: true, leader: a_leader)
      
      proc size*(self: var UnionFindTree, x: int): int =
        return -self.parent_or_size[self.find(x)]
      
      proc initUnionFindTree*(n: int): UnionFindTree =
        result = UnionFindTree(parent_or_size: newSeqWith(n, -1))
      

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
import byslib/ds/unionfind

proc main =
  type
    Q = tuple[t: range[1..3], x, y: int]
    E = tuple[a, b: int]

  let
    n, m = read(int)
    edges = newSeqWith(m):
      let
        a, b = read(int) - 1
        e: E = (a, b)
      e

    q = read(int)
    query = newSeqWith(q):
      let
        t = read(range[1..3])
        a, b = read(int) - 1
        qi: Q = (t, a, b)
      qi

  proc genUf(s: HashSet[E]): UnionFindTree =
    result = initUnionFindTree(n)
    for (a, b) in s:
      result.union(a, b)

  var
    edgeSet = edges.toHashSet()
    ufHist = initTable[int, UnionFindTree]()

  for i, (t, a, b) in query:
    let e: E = (a, b)
    case t
    of 1:
      ufHist[i] = genUf(edgeSet)
      edgeSet.incl(e)
    of 2:
      edgeSet.excl(e)
    of 3:
      discard

  var
    uf = genUf(edgeSet)
    ans = newSeq[string]()
  for i, (t, a, b) in query.reversed:
    let idx = q - i - 1
    case t
    of 1:
      uf = ufHist[idx]
    of 2:
      uf.union(a, b)
    of 3:
      ans.add(uf.same(a, b).tern("Yes", "No"))

  while ans.len > 0: print(ans.pop)

if isMainModule: main()
