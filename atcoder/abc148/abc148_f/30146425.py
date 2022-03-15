# from byslib.core.config import procon_setup
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.config = ModuleType("byslib.core.config")

_code_byslib = """
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.2"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core = """

"""
exec(_code_byslib_core, byslib.core.__dict__)

_code_byslib_core_config = """
import sys
from typing import Callable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    sys.setrecursionlimit(10**7)

    def wrapper(case: int = 1) -> None:
        for i in range(case):
            main(case=i + 1)

    return wrapper
"""
exec(_code_byslib_core_config, byslib.core.config.__dict__)

procon_setup = byslib.core.config.procon_setup
# from byslib.core.const import IINF, MOD
byslib.core.const = ModuleType("byslib.core.const")

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
# from byslib.core.fastio import debug, int1, readline, sinput
byslib.core.fastio = ModuleType("byslib.core.fastio")

_code_byslib_core_fastio = """
import io
import os
import sys
from functools import partial
from typing import Union

readline = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: Union[str, bytes]) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_fastio, byslib.core.fastio.__dict__)

debug = byslib.core.fastio.debug
int1 = byslib.core.fastio.int1
readline = byslib.core.fastio.readline
sinput = byslib.core.fastio.sinput
# from byslib.graph.breadth_first_search import breadth_first_search
byslib.graph = ModuleType("byslib.graph")
byslib.graph.breadth_first_search = ModuleType("byslib.graph.breadth_first_search")
byslib.graph.utility = ModuleType("byslib.graph.utility")
byslib.graph.edge = ModuleType("byslib.graph.edge")
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

    def pre_order(self, start: int) -> Generator[int, None, None]:
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

    def post_order(self, start: int) -> Generator[int, None, None]:
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

# from .depth_first_search import DepthFirstSearch
# from .edge import AdjacencyList, Edge

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
byslib.graph.utility.__dict__["DepthFirstSearch"] = byslib.graph.depth_first_search.DepthFirstSearch
byslib.graph.utility.__dict__["AdjacencyList"] = byslib.graph.edge.AdjacencyList
byslib.graph.utility.__dict__["Edge"] = byslib.graph.edge.Edge
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
# from byslib.graph.edge import AdjacencyList
AdjacencyList = byslib.graph.edge.AdjacencyList


@procon_setup
def main(**kwargs) -> None:
    n, u, v = map(int, readline().split())
    u -= 1
    v -= 1
    graph = AdjacencyList.init(n)
    for _ in range(n - 1):
        a, b = map(int1, readline().split())
        graph.add_edge(a, b)
        graph.add_edge(b, a)

    cost_u, _ = breadth_first_search(graph, u)
    cost_v, _ = breadth_first_search(graph, v)

    ans = 0
    for ui, vi in zip(cost_u, cost_v):
        if ui < vi:
            ans = max(ans, vi - 1)

    print(ans)


if __name__ == "__main__":
    t = 1
    # t = int(readline())
    main(t)


# package infomations
# --------------------------------------------------------------------------
# byslib-python
#   Version  : 0.0.2
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# --------------------------------------------------------------------------
