import sys

# from byslib.core import IINF, MOD, debug, sinput, int1
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")
byslib.core.io = ModuleType("byslib.core.io")

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

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

_code_byslib_core_io = """
import sys
from functools import partial


def sinput() -> str:
    return sys.stdin.readline().rstrip("\\r\\n")


def int1(s: str) -> int:
    return int(s) - 1


debug = partial(print, file=sys.stdout)
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

_code_byslib_core = """
# from .const import MOD, MOD7, INF, IINF
# from .io import debug, int1, sinput
"""
byslib.core.__dict__["MOD"] = byslib.core.const.MOD
byslib.core.__dict__["MOD7"] = byslib.core.const.MOD7
byslib.core.__dict__["INF"] = byslib.core.const.INF
byslib.core.__dict__["IINF"] = byslib.core.const.IINF
byslib.core.__dict__["debug"] = byslib.core.io.debug
byslib.core.__dict__["int1"] = byslib.core.io.int1
byslib.core.__dict__["sinput"] = byslib.core.io.sinput
exec(_code_byslib_core, byslib.core.__dict__)

IINF = byslib.core.IINF
MOD = byslib.core.MOD
debug = byslib.core.debug
sinput = byslib.core.sinput
int1 = byslib.core.int1
# from byslib.graph.edge import AdjacencyList
byslib.graph = ModuleType("byslib.graph")
byslib.graph.edge = ModuleType("byslib.graph.edge")

_code_byslib_graph = """
# graph
"""
exec(_code_byslib_graph, byslib.graph.__dict__)

_code_byslib_graph_edge = """
from typing import List, Iterable, Optional, overload, TypeVar
from collections import UserList


class Edge:
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

AdjacencyList = byslib.graph.edge.AdjacencyList


def main() -> None:
    n, q = map(int, sinput().split())
    x = list(map(int, sinput().split()))
    graph = AdjacencyList.init(n)
    for _ in range(n - 1):
        a, b = map(int1, sinput().split())
        graph.add_edge(a, b)
        graph.add_edge(b, a)

    dp = [[xi] for xi in x]

    def dfs(now: int, prev: int = -1) -> None:
        for to in graph[now]:
            if to.dest == prev:
                continue
            dfs(to.dest, now)
            for e in dp[to.dest]:
                dp[now].append(e)
        dp[now].sort(reverse=True)
        dp[now] = dp[now][: min(20, len(dp[now]))]

    dfs(0)

    for _ in range(q):
        v, k = map(int1, sinput().split())
        print(dp[v][k])


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
