import sys
if sys.argv[-1] == "ONLINE_JUDGE":
    from pathlib import Path
    # expand byslib
    __code = """\
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.1"

"""
    __path = Path("byslib/__init__.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

    # expand byslib.core
    __code = """\

"""
    __path = Path("byslib/core/__init__.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

    # expand byslib.core.const
    __code = """\
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2

"""
    __path = Path("byslib/core/const.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

    # expand byslib.core.io
    __code = """\
import sys
from functools import partial

readline = sys.stdin.buffer.readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: str) -> int:
    return int(s) - 1

"""
    __path = Path("byslib/core/io.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

    # expand byslib.data
    __code = """\
# data-structure

"""
    __path = Path("byslib/data/__init__.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

    # expand byslib.data.union_find
    __code = """\
from typing import List, Dict


class UnionFindTree:
    \"""Union-Find木\"""

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

"""
    __path = Path("byslib/data/union_find.py")
    __path.parent.mkdir(parents=True, exist_ok=True)
    __path.write_text(__code)

import sys

from byslib.core.const import IINF, MOD
from byslib.core.io import debug, sinput
from byslib.data.union_find import UnionFindTree


def main() -> None:
    n, q = map(int, sinput().split())
    uft = UnionFindTree(n + 1)
    for _ in range(q):
        l, r = map(int, sinput().split())
        uft.union(l - 1, r)
    print("Yes" if uft.same(0, n) else "No")


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()