import sys

# from byslib.core import IINF, MOD, debug, sinput
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")
byslib.core.io = ModuleType("byslib.core.io")

_code_byslib = """
# procon library

__version__ = "0.0.1"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

_code_byslib_core_io = """
import sys
from functools import partial


def sinput() -> str:
    return sys.stdin.readline().rstrip("\\r\\n")


def int1(s: str) -> int:
    return int(s) - 1


debug = partial(print, file=sys.stdout)
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

_code_byslib_core = """
# from .const import MOD, MOD7, INF, IINF
# from .io import debug, int1, sinput
"""
byslib.core.__dict__["MOD"] = byslib.core.const.MOD
byslib.core.__dict__["MOD7"] = byslib.core.const.MOD7
byslib.core.__dict__["INF"] = byslib.core.const.INF
byslib.core.__dict__["IINF"] = byslib.core.const.IINF
byslib.core.__dict__["debug"] = byslib.core.io.debug
byslib.core.__dict__["int1"] = byslib.core.io.int1
byslib.core.__dict__["sinput"] = byslib.core.io.sinput
exec(_code_byslib_core, byslib.core.__dict__)

IINF = byslib.core.IINF
MOD = byslib.core.MOD
debug = byslib.core.debug
sinput = byslib.core.sinput
# from byslib.data.union_find import UnionFindTree
byslib.data = ModuleType("byslib.data")
byslib.data.union_find = ModuleType("byslib.data.union_find")

_code_byslib_data = """
# data-structure
"""
exec(_code_byslib_data, byslib.data.__dict__)

_code_byslib_data_union_find = """
from typing import List, Dict


class UnionFindTree:
    \"""Union-Find木\"""

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
"""
exec(_code_byslib_data_union_find, byslib.data.union_find.__dict__)

UnionFindTree = byslib.data.union_find.UnionFindTree


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
