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
    fullname="byslib.data",
    is_package=True,
    code="""\
# @title Data Structure
""",
)

BundleImporter.add_module(
    fullname="byslib.data.union_find",
    is_package=False,
    code="""\
# @brief Union-Find Tree
from typing import Dict, List


class UnionFindTree:
    \"""Union-Find Tree
    Notes
    -----
    Time complexity

    * union : :math:`O(α(N))`
    * find : :math:`O(α(N))`

    Examples
    --------
    >>> uft = UnionFindTree(5)
    >>> uft.union(0, 4)
    True
    >>> uft.union(0, 3)
    True
    >>> print(uft.same(3, 4))
    True

    References
    ----------
    ..[1] 🐜 p.81
    \"""

    def __init__(self, n: int) -> None:
        self.n = n
        self.n_tree = n
        self.parent = [-1] * self.n  # 負なら親でありその値は(-子の数)

    def find(self, a: int) -> int:
        now = a
        path = []
        while self.parent[now] >= 0:
            path.append(now)
            now = self.parent[now]
        else:
            root = now

        for p in path:
            self.parent[p] = root

        return root

    def union(self, a: int, b: int) -> bool:
        root_a = self.find(a)
        root_b = self.find(b)

        if root_a == root_b:
            return False

        if -self.parent[root_a] > -self.parent[root_b]:
            root_a, root_b = root_b, root_a
        self.parent[root_b] += self.parent[root_a]
        self.parent[root_a] = root_b

        self.n_tree -= 1
        return True

    def same(self, a: int, b: int) -> bool:
        return self.find(a) == self.find(b)

    def size(self, a: int) -> int:
        return -self.parent[self.find(a)]

    def group(self) -> Dict[int, List[int]]:
        res: Dict[int, List[int]] = dict()
        for i in range(self.n):
            leader = self.find(i)
            if leader in res:
                res[leader].append(i)
            else:
                res[leader] = [i]

        return res


if __name__ == "__main__":
    import doctest

    doctest.testmod()
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.fastio import readline
from byslib.data.union_find import UnionFindTree


def dist2(a, b) -> int:
    res = 0
    for ai, bi in zip(a, b):
        res += (ai - bi) ** 2
    return res


@procon_setup
def main(**kwargs) -> None:
    n = int(readline())
    sx, sy, tx, ty = map(int, readline().split())
    s = (sx, sy)
    t = (tx, ty)
    c = [tuple(map(int, readline().split())) for _ in range(n)]

    uf = UnionFindTree(n + 2)
    for i in range(n):
        *pi, a = c[i]
        for j in range(i + 1, n):
            *pj, b = c[j]
            d = dist2(pi, pj)
            if (a + b) ** 2 >= d and abs(a - b) ** 2 <= d:
                uf.union(i, j)

        if dist2(pi, s) == a**2:
            uf.union(i, n)
        if dist2(pi, t) == a**2:
            uf.union(i, n + 1)

    print("Yes" if uf.same(n, n + 1) else "No")


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
