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

    return wrapper
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
    fullname="byslib.core.fastio",
    is_package=False,
    code="""\
# @title Fast I/O
import io
import os
import sys
from typing import Union

readline = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

if "USER" in os.environ:
    import inspect

    def debug(*args, sep: str = " ") -> None:
        line = inspect.getouterframes(inspect.currentframe())[1].lineno
        header = f"📌 line{line:>4}: "
        space = "\\n" + " " * (len(header) + 1)
        out = header + sep.join(map(str, args)).replace("\\n", space)
        print(out, file=sys.stderr)

else:

    def debug(*args, sep: str = " ") -> None:
        pass


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

sys.meta_path.append(BundleImporter)

from collections import deque

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, int1, readline, sinput
from byslib.graph import LilMatrix


@procon_setup
def main(**kwargs) -> None:
    n, m = map(int, readline().split())
    graph = LilMatrix.empty(n)
    for _ in range(m):
        u, v = map(int1, readline().split())
        graph.add_edge(u, v)
        graph.add_edge(v, u)

    seen = [False] * n
    st = [(0, -1)]
    while st:
        now, prev = st.pop()
        if not seen[now] and prev != -1:
            print(now + 1, prev + 1)
        seen[now] = True
        for dest, _ in graph[now]:
            if seen[dest]:
                continue
            st.append((dest, now))

    seen = [False] * n
    seen[0] = True
    que = deque([0])
    while que:
        now = que.popleft()
        for dest, _ in graph[now]:
            if seen[dest]:
                continue
            seen[dest] = True
            print(now + 1, dest + 1)
            que.append(dest)


if __name__ == "__main__":
    t = 1
    # t = int(readline())
    main(t)

# package infomations
# -----------------------------------------------------------------------------
# byslib-python
#   Version  : 0.1.0
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# -----------------------------------------------------------------------------
