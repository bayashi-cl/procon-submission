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
# from byslib.graph.dijkstra import dijkstra
byslib.graph = ModuleType("byslib.graph")
byslib.graph.dijkstra = ModuleType("byslib.graph.dijkstra")
byslib.graph.edge = ModuleType("byslib.graph.edge")

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

_code_byslib_graph_dijkstra = """
import heapq
from typing import List, Tuple

# from .edge import AdjacencyList
# from ..core.const import IINF


def dijkstra(graph: AdjacencyList, source: int) -> Tuple[List[int], List[int]]:
    n = len(graph)
    cost = [IINF] * n
    cost[source] = 0
    prev = [-1] * n
    que: List[Tuple[int, int]] = [(0, source)]
    while que:
        top_cost, top = heapq.heappop(que)
        if cost[top] < top_cost:
            continue
        for nxt in graph[top]:
            nxt_cost = cost[top] + nxt.weight
            if nxt_cost < cost[nxt.dest]:
                cost[nxt.dest] = nxt_cost
                prev[nxt.dest] = top
                heapq.heappush(que, (nxt_cost, nxt.dest))
    return cost, prev
"""
byslib.graph.dijkstra.__dict__["AdjacencyList"] = byslib.graph.edge.AdjacencyList
byslib.graph.dijkstra.__dict__["IINF"] = byslib.core.const.IINF
exec(_code_byslib_graph_dijkstra, byslib.graph.dijkstra.__dict__)

dijkstra = byslib.graph.dijkstra.dijkstra
# from byslib.graph.edge import AdjacencyList
AdjacencyList = byslib.graph.edge.AdjacencyList


def main() -> None:
    n = int(readline())
    graph = AdjacencyList.init(n)
    for _ in range(n - 1):
        u, v, w = map(int, readline().split())
        graph.add_edge(u - 1, v - 1, w)
        graph.add_edge(v - 1, u - 1, w)
    cost, _ = dijkstra(graph, 0)
    for c in cost:
        print(c % 2)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
