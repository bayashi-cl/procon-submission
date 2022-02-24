import sys

# from byslib.core.const import IINF, MOD
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")

_code_byslib = """
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.1"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core = """

"""
exec(_code_byslib_core, byslib.core.__dict__)

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

IINF = byslib.core.const.IINF
MOD = byslib.core.const.MOD
# from byslib.core.io import debug, readline, sinput
byslib.core.io = ModuleType("byslib.core.io")

_code_byslib_core_io = """
import sys
from functools import partial

readline = sys.stdin.buffer.readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: str) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

debug = byslib.core.io.debug
readline = byslib.core.io.readline
sinput = byslib.core.io.sinput
# from byslib.utility.grid import Grid
byslib.utility = ModuleType("byslib.utility")
byslib.utility.grid = ModuleType("byslib.utility.grid")

_code_byslib_utility = """

"""
exec(_code_byslib_utility, byslib.utility.__dict__)

_code_byslib_utility_grid = """
import typing


class Grid:
    DeltaItr = typing.Iterable[typing.Tuple[int, int]]
    h: int
    w: int

    def __init__(self, h: int, w: int) -> None:
        self.h = h
        self.w = w

    def __contains__(self, ij: typing.Tuple[int, int]) -> bool:
        return 0 <= ij[0] < self.h and 0 <= ij[1] < self.w

    def area(self) -> int:
        return self.h * self.w

    def index(self, i: int, j: int) -> int:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        return self.w * i + j

    def coord(self, ind: int) -> typing.Tuple[int, int]:
        if ind < 0 or self.area() <= ind:
            raise ValueError("index out of grid")
        return divmod(ind, self.w)

    def delta(self, i: int, j: int, d: DeltaItr) -> DeltaItr:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        for di, dj in d:
            ni, nj = i + di, j + dj
            if (ni, nj) in self:
                yield (ni, nj)

    def delta2(self, i: int, j: int) -> DeltaItr:
        return self.delta(i, j, ((0, 1), (1, 0)))

    def delta4(self, i: int, j: int) -> DeltaItr:
        return self.delta(i, j, ((-1, 0), (0, 1), (1, 0), (0, -1)))

    def delta8(self, i: int, j: int) -> DeltaItr:
        d = []
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di == 0 and dj == 0:
                    continue
                d.append((di, dj))
        return self.delta(i, j, d)
"""
exec(_code_byslib_utility_grid, byslib.utility.grid.__dict__)

Grid = byslib.utility.grid.Grid
# from byslib.graph.breadth_first_search import breadth_first_search
byslib.graph = ModuleType("byslib.graph")
byslib.graph.breadth_first_search = ModuleType("byslib.graph.breadth_first_search")
byslib.graph.edge = ModuleType("byslib.graph.edge")
byslib.graph.utility = ModuleType("byslib.graph.utility")
byslib.graph.depth_first_search = ModuleType("byslib.graph.depth_first_search")

_code_byslib_graph = """
# graph
"""
exec(_code_byslib_graph, byslib.graph.__dict__)

_code_byslib_graph_edge = """
from typing import List


class Edge:
    __slots__ = ("src", "dest", "weight")

    def __init__(self, src: int, dest: int, weight: int = 1) -> None:
        self.src = src
        self.dest = dest
        self.weight = weight

    def __lt__(self, rh: "Edge") -> bool:
        return self.weight < rh.weight

    def __repr__(self) -> str:
        return f"{{{self.src} -> {self.dest}: {self.weight}}}"


class AdjacencyList(List[List[Edge]]):
    def add_edge(self, src: int, dest: int, weight: int = -1) -> None:
        self[src].append(Edge(src, dest, weight))

    @classmethod
    def init(cls, n: int) -> "AdjacencyList":
        return cls([[] for _ in range(n)])
"""
exec(_code_byslib_graph_edge, byslib.graph.edge.__dict__)

_code_byslib_graph_depth_first_search = """
from typing import Generator, List

# from .edge import AdjacencyList


class DepthFirstSearch:
    cost: List[int]

    def __init__(self, graph: AdjacencyList) -> None:
        self.n = len(graph)
        self.graph = graph
        self.prev = [-1] * self.n

    def pre_order(self, start: int) -> Generator[int, int, None]:
        self.cost = [-1] * self.n
        self.cost[start] = 0
        que = [start]
        while que:
            now = que.pop()
            if now >= 0:
                yield now
                for nxt in self.graph[now]:
                    if self.cost[nxt.dest] != -1:
                        continue
                    self.cost[nxt.dest] = self.cost[now] + 1
                    self.prev[nxt.dest] = now
                    que.append(nxt.dest)

    def post_order(self, start: int) -> Generator[int, int, None]:
        self.cost = [-1] * self.n
        self.cost[start] = 0
        que = [~start, start]
        while que:
            now = que.pop()
            if now >= 0:
                for nxt in self.graph[now]:
                    if self.cost[nxt.dest] != -1:
                        continue
                    self.cost[nxt.dest] = self.cost[now] + 1
                    self.prev[nxt.dest] = now
                    que.append(~nxt.dest)
                    que.append(nxt.dest)

            else:
                yield ~now
"""
byslib.graph.depth_first_search.__dict__["AdjacencyList"] = byslib.graph.edge.AdjacencyList
exec(_code_byslib_graph_depth_first_search, byslib.graph.depth_first_search.__dict__)

_code_byslib_graph_utility = """
from typing import List, Tuple


# from .edge import AdjacencyList, Edge
# from .depth_first_search import DepthFirstSearch

SSSPResult = Tuple[List[int], List[int]]


def restore_path(prev: List[int], to: int) -> List[int]:
    res = []
    while to != -1:
        res.append(to)
        to = prev[to]
    return res[::-1]


def rooted_tree(graph: AdjacencyList, root: int) -> AdjacencyList:
    dfs = DepthFirstSearch(graph)
    res = AdjacencyList.init(len(graph))
    for now in dfs.pre_order(root):
        for nxt in graph[now]:
            if nxt.dest != dfs.prev[now]:
                res.add_edge(nxt.src, nxt.dest, nxt.weight)
    return res
"""
byslib.graph.utility.__dict__["AdjacencyList"] = byslib.graph.edge.AdjacencyList
byslib.graph.utility.__dict__["Edge"] = byslib.graph.edge.Edge
byslib.graph.utility.__dict__["DepthFirstSearch"] = byslib.graph.depth_first_search.DepthFirstSearch
exec(_code_byslib_graph_utility, byslib.graph.utility.__dict__)

_code_byslib_graph_breadth_first_search = """
from collections import deque
from typing import Deque

# from ..core.const import IINF
# from .edge import AdjacencyList
# from .utility import SSSPResult


def breadth_first_search(graph: AdjacencyList, source: int) -> SSSPResult:
    n = len(graph)
    prev = [-1] * n
    cost = [IINF] * n
    cost[source] = 0
    que: Deque[int] = deque()
    que.append(source)
    while que:
        top = que.popleft()
        for nxt in graph[top]:
            if cost[nxt.dest] == IINF:
                cost[nxt.dest] = cost[top] + 1
                prev[nxt.dest] = top
                que.append(nxt.dest)

    return cost, prev


def zero_one_bfs(graph: AdjacencyList, source: int, one: int = 1) -> SSSPResult:
    n = len(graph)
    cost = [IINF] * n
    cost[source] = 0
    prev = [-1] * n
    que: Deque[int] = deque()
    que.append(source)
    while que:
        top = que.popleft()
        for nxt in graph[top]:
            nxt_cost = cost[top] + nxt.weight
            if nxt_cost < cost[nxt.dest]:
                cost[nxt.dest] = nxt_cost
                prev[nxt.dest] = top
                if nxt.weight == 0:
                    que.appendleft(nxt.dest)
                elif nxt.weight == one:
                    que.append(nxt.dest)
                else:
                    raise ValueError

    return cost, prev
"""
byslib.graph.breadth_first_search.__dict__["IINF"] = byslib.core.const.IINF
byslib.graph.breadth_first_search.__dict__["AdjacencyList"] = byslib.graph.edge.AdjacencyList
byslib.graph.breadth_first_search.__dict__["SSSPResult"] = byslib.graph.utility.SSSPResult
exec(_code_byslib_graph_breadth_first_search, byslib.graph.breadth_first_search.__dict__)

breadth_first_search = byslib.graph.breadth_first_search.breadth_first_search
# from byslib.graph.edge import AdjacencyList, Edge
AdjacencyList = byslib.graph.edge.AdjacencyList
Edge = byslib.graph.edge.Edge


def main() -> None:
    offset = 205
    delta = [(1, 1), (0, 1), (-1, 1), (1, 0), (-1, 0), (0, -1)]
    grid = Grid(420, 420)

    n, x, y = map(int, readline().split())
    x += offset
    y += offset
    wall = set()
    for _ in range(n):
        wall.add(tuple(map(lambda x: int(x) + offset, readline().split())))

    s = grid.index(offset, offset)
    t = grid.index(x, y)

    graph = AdjacencyList.init(grid.area())
    for i in range(420):
        for j in range(420):
            if (i, j) in wall:
                continue
            now = grid.index(i, j)
            for ni, nj in grid.delta(i, j, delta):
                if (ni, nj) not in wall:
                    graph.add_edge(now, grid.index(ni, nj))

    cost, _ = breadth_first_search(graph, s)
    if cost[t] == IINF:
        print(-1)
    else:
        print(cost[t])


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
