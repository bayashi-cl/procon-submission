from typing import List

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
# from byslib.core.fastio import debug, readline, sinput
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
readline = byslib.core.fastio.readline
sinput = byslib.core.fastio.sinput
# from byslib.data.union_find import UnionFindTree
byslib.data = ModuleType("byslib.data")
byslib.data.union_find = ModuleType("byslib.data.union_find")

_code_byslib_data = """
# data-structure
"""
exec(_code_byslib_data, byslib.data.__dict__)

_code_byslib_data_union_find = """
from typing import Dict, List


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
exec(_code_byslib_data_union_find, byslib.data.union_find.__dict__)

UnionFindTree = byslib.data.union_find.UnionFindTree
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


def judge(s: List[List[str]], n: int, m: int) -> bool:
    wall = sum(si.count("#") for si in s)
    grid = Grid(n, m)
    dsu = UnionFindTree(grid.area())

    for i in range(n):
        for j in range(m):
            if s[i][j] == "#":
                continue
            for ni, nj in grid.delta4(i, j):
                if s[ni][nj] == ".":
                    dsu.union(grid.index(i, j), grid.index(ni, nj))
    return dsu.n_tree == wall + 1


@procon_setup
def main(**kwargs) -> None:
    n, m = map(int, readline().split())
    s = [list(sinput()) for _ in range(n)]
    ans = 0
    for i in range(n):
        for j in range(m):
            if s[i][j] == ".":
                continue
            s[i][j] = "."
            if judge(s, n, m):
                ans += 1
            s[i][j] = "#"

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
