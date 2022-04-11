import os
import sys
from importlib.machinery import ModuleSpec, SourceFileLoader


class BundleImporter(SourceFileLoader):
    """Importer that supports importing from strings in code.

    This class is automatically generated by expander.
    """

    module_ispkg = dict()
    module_code = dict()

    @classmethod
    def add_module(cls, fullname, is_package, code):
        cls.module_ispkg[fullname] = is_package
        cls.module_code[cls.get_filename(fullname)] = bytes(code, encoding="utf-8")

    @classmethod
    def find_spec(cls, fullname, path=None, target=None):
        if fullname in cls.module_ispkg:
            return ModuleSpec(
                fullname,
                cls(fullname, ""),
                is_package=cls.module_ispkg[fullname],
            )
        else:
            return None

    @classmethod
    def get_filename(cls, fullname):
        return fullname.replace(".", "_") + ".py"

    def get_data(self, path):
        try:
            return self.module_code[path]
        except KeyError:
            with open(path, "rb") as file:
                return file.read()

    def path_stats(self, path):
        return {"mtime": os.stat(__file__).st_mtime, "size": None}

BundleImporter.add_module(
    fullname="byslib",
    is_package=True,
    code="""\
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.2"
""",
)

BundleImporter.add_module(
    fullname="byslib.core",
    is_package=True,
    code="""\
""",
)

BundleImporter.add_module(
    fullname="byslib.core.config",
    is_package=False,
    code="""\
import sys
from typing import Callable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    sys.setrecursionlimit(10**7)

    def wrapper(case: int = 1) -> None:
        for i in range(case):
            main(case=i + 1)

    return wrapper
""",
)

BundleImporter.add_module(
    fullname="byslib.core.const",
    is_package=False,
    code="""\
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
""",
)

BundleImporter.add_module(
    fullname="byslib.core.fastio",
    is_package=False,
    code="""\
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
""",
)

BundleImporter.add_module(
    fullname="byslib.graph",
    is_package=True,
    code="""\
# graph
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.breadth_first_search",
    is_package=False,
    code="""\
from collections import deque
from typing import Deque, List, Union

from ..core.const import IINF
from .edge import AdjacencyList
from .utility import SSSPResult


def breadth_first_search(
    graph: AdjacencyList, source: Union[int, List[int]]
) -> SSSPResult:
    n = len(graph)
    prev = [-1] * n
    cost = [IINF] * n
    if isinstance(source, int):
        cost[source] = 0
        que: Deque[int] = deque([source])
    elif isinstance(source, list):
        for s in source:
            cost[s] = 0
        que = deque(source)
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
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.edge",
    is_package=False,
    code="""\
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
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.utility",
    is_package=False,
    code="""\
from typing import List, Tuple

from .depth_first_search import DepthFirstSearch
from .edge import AdjacencyList, Edge

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
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.depth_first_search",
    is_package=False,
    code="""\
from typing import Generator, List

from .edge import AdjacencyList


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
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, int1, readline, sinput
from byslib.graph.breadth_first_search import breadth_first_search
from byslib.graph.edge import AdjacencyList


@procon_setup
def main(**kwargs) -> None:
    n, m, k = map(int, readline().split())
    h = list(map(int, readline().split()))
    c = list(map(int1, readline().split()))
    graph = AdjacencyList.init(n)
    for _ in range(m):
        a, b = map(int1, readline().split())
        if h[a] > h[b]:
            a, b = b, a
        graph.add_edge(a, b, 1)

    cost, _ = breadth_first_search(graph, c)
    print(*map(lambda x: -1 if x == IINF else x, cost), sep="\n")


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
