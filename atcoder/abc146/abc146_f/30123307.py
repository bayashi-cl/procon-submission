from typing import Tuple

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

__version__ = "0.0.1"
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

readline = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: str) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_fastio, byslib.core.fastio.__dict__)

debug = byslib.core.fastio.debug
readline = byslib.core.fastio.readline
sinput = byslib.core.fastio.sinput
# from byslib.data.segment_tree import SegmentTree
byslib.data = ModuleType("byslib.data")
byslib.data.segment_tree = ModuleType("byslib.data.segment_tree")

_code_byslib_data = """
# data-structure
"""
exec(_code_byslib_data, byslib.data.__dict__)

_code_byslib_data_segment_tree = """
from typing import List, TypeVar, Generic, Callable

T = TypeVar("T")


class SegmentTree(Generic[T]):
    def __init__(self, op: Callable[[T, T], T], ident: T, val: List[T]) -> None:
        self.op = op
        self.ident = ident
        self.n = len(val)
        self.n_leaf = 1 << (self.n - 1).bit_length()
        self.data = [self.ident] * (self.n_leaf * 2)
        self.data[self.n_leaf : self.n_leaf + self.n] = val
        for i in range(self.n_leaf - 1, 0, -1):
            self.data[i] = self.op(self.data[i * 2], self.data[i * 2 + 1])

    def update(self, i: int, v: T) -> None:
        i += self.n_leaf
        self.data[i] = v
        i >>= 1
        while i > 0:
            self.data[i] = self.op(self.data[i * 2], self.data[i * 2 + 1])
            i >>= 1

    def query(self, l: int, r: int) -> T:
        left = self.ident
        right = self.ident
        l += self.n_leaf
        r += self.n_leaf
        while l < r:
            if l & 1:
                left = self.op(left, self.data[l])
                l += 1
            if r & 1:
                r -= 1
                right = self.op(self.data[r], right)
            l >>= 1
            r >>= 1
        return self.op(left, right)

    def query_all(self) -> T:
        return self.data[1]

    def __getitem__(self, key: int) -> T:
        return self.data[key + self.n_leaf]

    @classmethod
    def empty(cls, op: Callable[[T, T], T], ident: T, n: int) -> "SegmentTree":
        return cls(op, ident, [ident] * n)
"""
exec(_code_byslib_data_segment_tree, byslib.data.segment_tree.__dict__)

SegmentTree = byslib.data.segment_tree.SegmentTree

Pa = Tuple[int, int]


@procon_setup
def main(**kwargs) -> None:
    n, m = map(int, readline().split())
    s = sinput()
    prev = [0] * (n + 1)
    seg: SegmentTree[Pa] = SegmentTree.empty(min, (IINF, IINF), n + 1)
    seg.update(0, (0, 0))
    for i, si in enumerate(s):
        if si == "1":
            continue
        mi = seg.query(max(i - m, 0), i)
        if mi[0] != IINF:
            seg.update(i, (mi[0] + 1, i))
            prev[i] = i - mi[1]

    if seg[n][0] == IINF:
        print(-1)
        return

    ans = []
    while n > 0:
        ans.append(prev[n])
        n -= prev[n]

    print(*ans[::-1])


if __name__ == "__main__":
    t = 1
    # t = int(readline())
    main(t)
