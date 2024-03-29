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
            return super().get_data(path)
        except OSError:
            try:
                return self.module_code[path]
            except KeyError:
                raise OSError

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

__version__ = "0.1.0"
""",
)

BundleImporter.add_module(
    fullname="byslib.core",
    is_package=True,
    code="""\
# @title Core Featule
""",
)

BundleImporter.add_module(
    fullname="byslib.core.config",
    is_package=False,
    code="""\
# @title setup
import sys
from typing import Callable

from .fastio import readable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    \"""setup

    Notes
    -----
    * Set recursionlimit to 1e7
    * Repeat main function for testcases
    * If exception raised, indicate in which test case it was raised.
    \"""

    def wrapper(case: int = 1) -> None:
        sys.setrecursionlimit(10**7)
        for i in range(case):
            try:
                main(case=i + 1)
            except Exception as e:
                print(
                    f"❌ {type(e).__name__} raised in tastcase {i + 1}.",
                    file=sys.stderr,
                )
                raise

        if readable():
            print("🔺 Unused inputs.", file=sys.stderr)

    return wrapper
""",
)

BundleImporter.add_module(
    fullname="byslib.core.fastio",
    is_package=False,
    code="""\
# @title Fast I/O
import io
import os
import sys
from typing import Union

if "USER" in os.environ:
    import inspect

    stdin = sys.stdin.buffer

    def debug(*args, sep: str = " ") -> None:
        line = inspect.getouterframes(inspect.currentframe())[1].lineno
        header = f"📌 line{line:>4}: "
        space = "\\n" + " " * (len(header) + 1)
        out = header + sep.join(map(str, args)).replace("\\n", space)
        print(out, file=sys.stderr)

else:
    stdin = io.BytesIO(os.read(0, os.fstat(0).st_size))

    def debug(*args, sep: str = " ") -> None:
        pass


readline = stdin.readline


def readable() -> bool:
    return len(stdin.read()) != 0


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: Union[str, bytes]) -> int:
    return int(s) - 1
""",
)

BundleImporter.add_module(
    fullname="byslib.core.const",
    is_package=False,
    code="""\
# @title Const
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
""",
)

BundleImporter.add_module(
    fullname="byslib.graph",
    is_package=True,
    code="""\
# @title Graph
from .edge import Edge
from .graph import LilMatrix
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.edge",
    is_package=False,
    code="""\
# @title Edge
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
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.graph",
    is_package=False,
    code="""\
# @title Adjacency List
from typing import List, Tuple


class LilMatrix(List[List[Tuple[int, int]]]):
    \"""List in List Matrix\"""

    @classmethod
    def empty(cls, n: int) -> "LilMatrix":
        return cls([[] for _ in range(n)])

    def add_edge(self, src: int, dest: int, weight: int = 1) -> None:
        self[src].append((dest, weight))
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.breadth_first_search",
    is_package=False,
    code="""\
# @title Breadth First Search
from collections import deque
from typing import Deque, Iterable, List, Tuple, Union

from ..core.const import IINF
from .graph import LilMatrix


def breadth_first_search(
    graph: LilMatrix, source: Union[int, Iterable[int]]
) -> Tuple[List[int], List[int]]:
    \"""BFS

    Parameters
    ----------
    graph
        (Un)Weighted graph
    source
        source or list of source

    Returns
    -------
        (cost, prev)

    Notes
    -----
    Time complexity

    O(V + E)

    References
    ----------
    ..[1] 🐜 p.36
    \"""
    n = len(graph)
    prev = [-1] * n
    cost = [IINF] * n

    if isinstance(source, int):
        cost[source] = 0
        que: Deque[int] = deque([source])
    else:
        for s in source:
            cost[s] = 0
        que = deque(source)

    while que:
        top = que.popleft()
        for dest, _ in graph[top]:
            if cost[dest] == IINF:
                cost[dest] = cost[top] + 1
                prev[dest] = top
                que.append(dest)

    return cost, prev


def zero_one_bfs(
    graph: LilMatrix, source: Union[int, Iterable[int]], one: int = 1
) -> Tuple[List[int], List[int]]:
    \"""01BFS

    Parameters
    ----------
    graph
        Weighted graph
    source
        source or list of source
    one
        cost of `one`

    Returns
    -------
        (cost, prev)

    Notes
    -----
    Time complexity

    O(V + E)
    \"""
    n = len(graph)
    cost = [IINF] * n
    prev = [-1] * n

    if isinstance(source, int):
        cost[source] = 0
        que: Deque[int] = deque([source])
    else:
        for s in source:
            cost[s] = 0
        que = deque(source)

    while que:
        top = que.popleft()
        for dest, weight in graph[top]:
            nxt_cost = cost[top] + weight
            if nxt_cost < cost[dest]:
                cost[dest] = nxt_cost
                prev[dest] = top
                if weight == 0:
                    que.appendleft(dest)
                elif weight == one:
                    que.append(dest)
                else:
                    raise ValueError

    return cost, prev
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.utility",
    is_package=False,
    code="""\
# @title Graph Utility
from typing import List, Tuple

from .depth_first_search import DepthFirstSearch
from .graph import LilMatrix


def restore_path(prev: List[int], to: int) -> List[int]:
    res = []
    while to != -1:
        res.append(to)
        to = prev[to]
    return res[::-1]


def rooted_tree(graph: LilMatrix, root: int) -> LilMatrix:
    dfs = DepthFirstSearch(graph)
    res = LilMatrix.empty(len(graph))
    for now in dfs.pre_order(root):
        for dest, weight in graph[now]:
            if dest != dfs.prev[now]:
                res.add_edge(now, dest, weight)
    return res
""",
)

BundleImporter.add_module(
    fullname="byslib.graph.depth_first_search",
    is_package=False,
    code="""\
# @title Depth First Search
from typing import Generator, List

from .graph import LilMatrix


class DepthFirstSearch:
    \"""DFS

    pre-order and post-order generator

    Notes
    -----
    Time complexity

    O(V + E)

    References
    ----------
    ..[1] 🐜 p.33
    \"""

    cost: List[int]

    def __init__(self, graph: LilMatrix) -> None:
        \"""Parameters
        ----------
        graph
            (Un)Weighted graph
        \"""
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
                for dest, _ in self.graph[now]:
                    if self.cost[dest] != -1:
                        continue
                    self.cost[dest] = self.cost[now] + 1
                    self.prev[dest] = now
                    que.append(dest)

    def post_order(self, start: int) -> Generator[int, None, None]:
        self.cost = [-1] * self.n
        self.cost[start] = 0
        que = [~start, start]
        while que:
            now = que.pop()
            if now >= 0:
                for dest, _ in self.graph[now]:
                    if self.cost[dest] != -1:
                        continue
                    self.cost[dest] = self.cost[now] + 1
                    self.prev[dest] = now
                    que.append(~dest)
                    que.append(dest)

            else:
                yield ~now
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, int1, readline, sinput
from byslib.graph import LilMatrix
from byslib.graph.breadth_first_search import breadth_first_search as bfs
from byslib.graph.utility import restore_path


@procon_setup
def main(**kwargs) -> None:
    n, x, y = map(int, readline().split())
    x -= 1
    y -= 1
    graph = LilMatrix.empty(n)
    for _ in range(n - 1):
        u, v = map(int1, readline().split())
        graph.add_edge(u, v)
        graph.add_edge(v, u)

    _, prev = bfs(graph, x)
    path = restore_path(prev, y)
    print(*map(lambda x: x + 1, path))


if __name__ == "__main__":
    t = 1  # * int(readline())
    main(t)

# package infomations
# -----------------------------------------------------------------------------
# byslib-python
#   Version  : 0.1.0
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# -----------------------------------------------------------------------------
