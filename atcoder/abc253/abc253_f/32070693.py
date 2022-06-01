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
    fullname="byslib.data.binary_indexed_tree",
    is_package=False,
    code="""\
# @title Bynary Indexed Tree
from typing import List


class BinaryIndexedTree:
    r\"""Bynary Indexed Tree (Fenwick Tree)

    Notes
    -----
    Time complexity

    * Build : :math:`O(N)`
    * Point_append : :math:`O(\\log(N))`
    * Fold : :math:`O(\\log(N))`

    References
    ----------
    ..[1] 🐜 p.159
    ..[2] https://scrapbox.io/data-structures/Fenwick_Tree

    Examples
    --------
    >>> bit = BinaryIndexedTree.zeros(5)
    >>> bit.point_append(0, 3)
    >>> bit.point_append(2, -2)
    >>> print(bit.fold(1, 4))
    -2
    \"""

    def __init__(self, array: List[int]) -> None:
        self.size = len(array)
        self.data = [0] * (self.size + 1)
        for i, ai in enumerate(array):
            self.point_append(i, ai)

    def point_append(self, index: int, value: int) -> None:
        index += 1
        while index <= self.size:
            self.data[index] += value
            index += index & -index

    def prefix_fold(self, right: int) -> int:
        s = 0
        while right > 0:
            s += self.data[right]
            right -= right & -right
        return s

    def fold(self, left: int, right: int) -> int:
        return self.prefix_fold(right) - self.prefix_fold(left)

    @classmethod
    def zeros(cls, n: int) -> "BinaryIndexedTree":
        return cls([0] * n)
""",
)

sys.meta_path.append(BundleImporter)

from typing import List, Optional, Tuple

from byslib.core.config import procon_setup
from byslib.core.fastio import readline
from byslib.data.binary_indexed_tree import BinaryIndexedTree


@procon_setup
def main(**kwargs) -> None:
    n, m, q = map(int, readline().split())

    query: List[Tuple[int, ...]] = []
    prev: List[Optional[Tuple[int, int]]] = [None] * n
    sub: List[List[Tuple[int, int]]] = [[] for _ in range(q)]

    type_3 = [False] * q
    ans = [0] * q

    for qi in range(q):
        t, *body = map(int, readline().split())
        if t == 1:
            l, r, x = body
            query.append((t, l - 1, r, x))
        elif t == 2:
            i, x = body
            query.append((t, i - 1, x))
            prev[i - 1] = (qi, x)
        else:  # t == 3
            type_3[qi] = True
            i, j = body
            query.append((t, i - 1, j))

            update = prev[i - 1]
            if update is not None:
                p, x = update
                ans[qi] += x
                sub[p].append((qi, j))

    bit = BinaryIndexedTree.zeros(m + 1)
    for qi, que in enumerate(query):
        t, *body = que

        if t == 1:
            l, r, x = body
            bit.point_append(l, x)
            bit.point_append(r, -x)
        elif t == 2:
            for idx, j in sub[qi]:
                ans[idx] -= bit.prefix_fold(j)
        else:  # t == 3
            _, j = body
            ans[qi] += bit.prefix_fold(j)

    for ai, flg in zip(ans, type_3):
        if flg:
            print(ai)


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