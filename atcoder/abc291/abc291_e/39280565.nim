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
      

    writeModule("atcoder/dsu.nim"):
      when not declared ATCODER_DSU_HPP:
        const ATCODER_DSU_HPP* = 1
      
        import std/sequtils
      
        type
          DSU* = ref object
            n: int
            par_or_siz: seq[int]
      
        proc initDSU*(n: int): DSU {.inline.} =
          return DSU(n: n, par_or_siz: newSeqWith(n, -1))
      
        proc leader*(self: DSU; a: int): int {.inline.} =
          ## Path compression
          if self.par_or_siz[a] < 0: return a
          self.par_or_siz[a] = self.leader(self.par_or_siz[a])
          return self.par_or_siz[a]
      
        proc same*(self: DSU; a, b: int): bool {.inline.} =
          self.leader(a) == self.leader(b)
      
        proc size*(self: DSU; a: int): int {.inline.} =
          - self.par_or_siz[self.leader(a)]
      
        proc merge*(self: DSU; a, b: int): int {.inline, discardable.} =
      
          var
            x = self.leader(a)
            y = self.leader(b)
      
          if x == y: return x
          if self.par_or_siz[x] > self.par_or_siz[y]: swap(x, y)
          self.par_or_siz[x] += self.par_or_siz[y]
          self.par_or_siz[y] = x
          return x
      
        proc groups*(self: DSU): seq[seq[int]] {.inline.} =
          var
            leaderBuf = newSeq[int](self.n)
            groupsize = newSeq[int](self.n)
          for i in 0 ..< self.n:
            leaderBuf[i] = self.leader(i)
            groupsize[leaderBuf[i]].inc
          result = (0 ..< self.n).mapIt(newSeqOfCap[int](groupsize[it]))
          for i, ldr in leaderBuf:
            result[ldr].add i
          result.keepItIf(it.len > 0)
      

    writeModule("atcoder/extra/graph/graph_template.nim"):
      when not declared ATCODER_GRAPH_TEMPLATE_HPP:
        const ATCODER_GRAPH_TEMPLATE_HPP* = 1
        import std/sequtils, std/tables
      
        type
          ADJTYPE_SEQ* = object
          ADJTYPE_TABLE* = object
          ADJTYPE_PROC* = object
          ADJTYPE_ITER* = object
          USEID_TRUE* = object
          USEID_FALSE* = object
      #    Edge*[T] = ref object
          Edge*[T, U] = object
            src*,dst*:U
            weight*:T
            rev*:int
          Edges*[T, U] = seq[Edge[T, U]]
          Graph*[T, U, adjType, useId] = object
            len*:int
            when adjType is ADJTYPE_SEQ:
              adj*: seq[seq[Edge[T, U]]]
            elif adjType is ADJTYPE_TABLE:
              adj*: Table[U, seq[Edge[T, U]]]
            elif adjType is ADJTYPE_ITER:
              adj_iter*: iterator(u:U):tuple[dst:U, weight:T]
            elif adjType is ADJTYPE_PROC:
              adj*: proc(u:U):seq[tuple[dst:U, weight:T]]
            else:
              discard
            when useId is USEID_TRUE:
              id*:proc(u:U):int
          Matrix*[T] = seq[seq[T]]
      
        proc `@`*(e:Edge):auto = e.weight
      
        proc initEdge*[T, U](src,dst:U,weight:T = 1,rev:int = -1):Edge[T, U] =
          return Edge[T, U](src:src, dst:dst, weight:weight, rev:rev)
        proc `<`*[T, U](a, b:Edge[T, U]):bool = a.weight < b.weight
        
        proc initGraph*(n:int, T:typedesc = int, U:typedesc[int] = int):Graph[T, U, ADJTYPE_SEQ, USEID_FALSE] =
          return Graph[T, int, ADJTYPE_SEQ, USEID_FALSE](len:n, adj:newSeqWith(n, newSeq[Edge[T, U]]()))
        proc initGraph*(T:typedesc = int, U:typedesc = int):Graph[T, U, ADJTYPE_TABLE, USEID_FALSE] =
          return Graph[T, U, ADJTYPE_TABLE, USEID_FALSE](len: 0, adj:initTable[U, seq[Edge[T, U]]]())
      
        proc initGraph*[U](n:int, id:proc(u:U):int, T:typedesc = int):Graph[T, U, ADJTYPE_SEQ, USEID_TRUE] =
          return Graph[T, U, ADJTYPE_SEQ, USEID_TRUE](len:n, adj:newSeqWith(n,newSeq[Edge[T, U]]()), id:id)
        proc initGraph*[T, U](n:int, id:proc(u:U):int, adj:proc(u:U):seq[(U, T)]):Graph[T, U, ADJTYPE_PROC, USEID_TRUE] =
          return Graph[T, U, ADJTYPE_PROC, USEID_TRUE](len:n, adj:adj, id:id)
        proc initGraph*[T, U](n:int, id:proc(u:U):int, adj_iter:iterator(u:U):(U, T)):Graph[T, U, ADJTYPE_ITER, USEID_TRUE] =
          return Graph[T, U, ADJTYPE_ITER, USEID_TRUE](len:n, adj_iter:adj_iter, id:id)
        proc initGraph*[T, U](adj:proc(u:U):seq[(U, T)]):auto =
          return Graph[T, U, ADJTYPE_PROC, USEID_FALSE](len:0, adj:adj)
        proc initGraph*[T, U](adj_iter:iterator(u:U):(U, T)):auto =
          return Graph[T, U, ADJTYPE_ITER, USEID_FALSE](len:0, adj_iter:adj_iter)
      
        template `[]`*[G:Graph](g:G, u:G.U):auto =
          when G.adjType is ADJTYPE_SEQ:
            when u is int: g.adj[u]
            else: g.adj[g.id(u)]
          elif G.adjType is ADJTYPE_TABLE:
            if u notin g.adj:
              g.adj[u] = newSeq[Edge[G.T, G.U]]()
            g.adj[u]
          else:
            g.adj(u)
      
        proc addBiEdge*[T, U, adjType, useId](g:var Graph[T, U, adjType, useId], e:Edge[T, U]):void =
          when adjType is ADJTYPE_SEQ | ADJTYPE_TABLE:
      #    var e_rev = initEdge[T](e.src, e.dst, e.weight, e.rev)
            if e.src != e.dst:
              var e_rev = e
              swap(e_rev.src, e_rev.dst)
              let (r, s) = (g[e.src].len, g[e.dst].len)
              g[e.src].add(e)
              g[e.dst].add(e_rev)
              g[e.src][^1].rev = s
              g[e.dst][^1].rev = r
            else:
              let r = g[e.src].len
              g[e.src].add(e)
              g[e.src][^1].rev = r
          else:
            static_assert false
      
        proc addBiEdge*[T, U, adjType, useId](g:var Graph[T, U, adjType, useId],src,dst:U,weight:T = 1):void =
          g.addBiEdge(initEdge(src, dst, weight))
      
        proc addEdge*[T, U, adjType, useId](g:var Graph[T, U, adjType, useId], e:Edge[T, U]) = g[e.src].add(e)
        proc addEdge*[T, U, adjType, useId](g:var Graph[T, U, adjType, useId], src, dst:U, weight:T = 1):void =
          g.addEdge(initEdge[T, U](src, dst, weight, -1))
      
        proc initUndirectedGraph*[T, U](n:int, a,b:seq[U], c:seq[T]):Graph[T, U, ADJTYPE_SEQ, USEID_FALSE] =
          result = initGraph[T](n, U)
          for i in 0..<a.len: result.addBiEdge(a[i], b[i], c[i])
        proc initUndirectedGraph*[U](n:int, a,b:seq[U]):Graph[int, U, ADJTYPE_SEQ, USEID_FALSE] =
          result = initGraph[int](n, U)
          for i in 0..<a.len: result.addBiEdge(a[i], b[i])
        proc initDirectedGraph*[T, U](n:int, a,b:seq[U],c:seq[T]):Graph[T, U, ADJTYPE_SEQ, USEID_FALSE] =
          result = initGraph[T](n, U)
          for i in 0..<a.len: result.addEdge(a[i], b[i], c[i])
        proc initDirectedGraph*[U](n:int, a,b:seq[U]):Graph[int, U, ADJTYPE_SEQ, USEID_FALSE] =
          result = initGraph[int](n, U)
          for i in 0..<a.len: result.addEdge(a[i], b[i])
      
        template id*[G:Graph](g:G, u:int):int = 
          when G.U is int: u
          else: g.id(u)
      
        iterator adj*[T, U, useID](g:Graph[T, U, ADJTYPE_ITER, useID], u:U):tuple[dst:U, weight:T] =
          var iter:type(g.adj_iter)
          iter.deepCopy(g.adj_iter)
          for e in iter(u):
            yield e
      
        iterator adj_by_id*[G:Graph](g:G, u:int):auto =
          when G.adjType is ADJTYPE_SEQ:
            for e in g.adj[u]: yield e
          else:
            for e in g.adj(u): yield e
      
        type NodeArray*[U, VAL, useId] = object
          default_val*:VAL
          when useId is USEID_TRUE:
            id*: proc(u:U):int
          when useId is USEID_TRUE or U is int:
            v*:seq[VAL]
          else:
            v*:Table[U, VAL]
      
        proc initNodeArray*[VAL](g:Graph, default_val:VAL, len = 0):auto =
          result = NodeArray[g.U, VAL, g.useId](default_val:default_val)
          when g.useId is USEID_TRUE or g.U is int:
            if len > 0:
              result.v = newSeqWith(len, default_val)
          when g.useId is USEID_TRUE:
            result.id = g.id
      
        proc `[]`*[U, useId, VAL](a:var NodeArray[U, VAL, useId], u:U):ptr[VAL] =
          when useId is USEID_TRUE or U is int:
            when U is int:
              var i = u
            else:
              var i = a.id(u)
            while i >= a.v.len:
              a.v.add a.default_val
            a.v[i].addr
          else:
            if u notin a.v:
              (a.v)[u] = a.default_val
            a.v[u].addr
      
        proc contains*[U, useId, VAL](a:var NodeArray[U, VAL, useId], u:U):bool =
          when useId is USEID_TRUE or U is int:
            when U is int:
              var i = u
            else:
              var i = a.id(u)
            return i < a.v.len
          else:
            return u in a.v
      

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

import atcoder/dsu
import atcoder/extra/graph/graph_template
# import atcoder/extra/graph/topological_sort

# Topological Sort {{{
when not declared ATCODER_TOPOLOGICAL_SORT_HPP:
  const ATCODER_TOPOLOGICAL_SORT_HPP* = 1
  # import atcoder/extra/graph/graph_template
  proc topologicalSort*(g: Graph): seq[int] =
    let N = g.len
    var deg = newSeq[int](N)
    for i in 0..<N:
      for e in g[i]:
        deg[e.dst].inc
    var st = newSeq[int]()
    for i in 0..<N:
      if deg[i] == 0: st.add(i)
    result = newSeq[int]()
    while st.len == 1:
      let p = st.pop()
      result.add(p)
      for e in g[p]:
        deg[e.dst].dec
        if deg[e.dst] == 0: st.add(e.dst)
# }}}

proc main =
  let n, m = read(int)
  var
    graph = initGraph(n)
    uf = initDSU(n)

  m.times:
    let x, y = read(int) - 1
    graph.addEdge(x, y)
    uf.merge(x, y)

  if uf.size(0) != n:
    print("No")
    return

  let res = graph.topologicalSort()
  if res.len() != n:
    print("No")
    return

  var ans = newSeq[int](n)

  for i in countdown(n-1, 0, 1):
    ans[res[i]] = i + 1

  print("Yes")
  print(ans)

if isMainModule: main()
