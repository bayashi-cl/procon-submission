import types

_byslib_code = r'''
# procon library

__version__ = "0.0.1"
'''

byslib = types.ModuleType('byslib')
exec(_byslib_code, byslib.__dict__)


_byslib_core_code = r'''
# core
'''

byslib.core = types.ModuleType('byslib.core')
exec(_byslib_core_code, byslib.core.__dict__)

_byslib_core_const_code = r'''
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
'''

byslib.core.const = types.ModuleType('byslib.core.const')
exec(_byslib_core_const_code, byslib.core.const.__dict__)
IINF = byslib.core.const.IINF

INF = byslib.core.const.INF

MOD = byslib.core.const.MOD

MOD7 = byslib.core.const.MOD7



_byslib_core_io_code = r'''
import sys
from functools import partial


def sinput() -> str:
    return sys.stdin.readline().rstrip("\r\n")


def int1(s: str) -> int:
    return int(s) - 1


debug = partial(print, file=sys.stdout)
'''

byslib.core.io = types.ModuleType('byslib.core.io')
exec(_byslib_core_io_code, byslib.core.io.__dict__)
debug = byslib.core.io.debug

int1 = byslib.core.io.int1

sinput = byslib.core.io.sinput



_byslib_data_code = r'''
# data-structure
'''

byslib.data = types.ModuleType('byslib.data')
exec(_byslib_data_code, byslib.data.__dict__)

_byslib_data_union_find_code = r'''
from typing import List, Dict


class UnionFindTree:
    """Union-Find木"""

    def __init__(self, n: int) -> None:
        self.n = n
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
'''

byslib.data.union_find = types.ModuleType('byslib.data.union_find')
exec(_byslib_data_union_find_code, byslib.data.union_find.__dict__)
UnionFindTree = byslib.data.union_find.UnionFindTree

import sys
from typing import Callable, Dict, List, Set, Tuple

# from byslib.core.const import IINF, INF, MOD, MOD7
# from byslib.core.io import debug, int1, sinput
# from byslib.data.union_find import UnionFindTree


def main() -> None:
    n, q = map(int, sinput().split())
    uft = UnionFindTree(n + 1)
    for _ in range(q):
        l, r = map(int, sinput().split())
        uft.union(l - 1, r)
    print("Yes" if uft.same(0, n) else "No")


if __name__ == "__main__":
    sys.setrecursionlimit(10 ** 6)
    main()
