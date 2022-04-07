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
# from byslib.core.fastio import int1, readline
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

int1 = byslib.core.fastio.int1
readline = byslib.core.fastio.readline
# from byslib.data.union_find import UnionFindTree
byslib.data = ModuleType("byslib.data")
byslib.data.union_find = ModuleType("byslib.data.union_find")

_code_byslib_data = """
# data-structure
"""
exec(_code_byslib_data, byslib.data.__dict__)

_code_byslib_data_union_find = """
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
"""
exec(_code_byslib_data_union_find, byslib.data.union_find.__dict__)

UnionFindTree = byslib.data.union_find.UnionFindTree


@procon_setup
def main(**kwargs) -> None:
    n, m, k = map(int, readline().split())
    uft = UnionFindTree(n)
    exclude = [1] * n
    for _ in range(m):
        a, b = map(int1, readline().split())
        uft.union(a, b)
        exclude[a] += 1
        exclude[b] += 1

    for _ in range(k):
        c, d = map(int1, readline().split())
        if uft.same(c, d):
            exclude[c] += 1
            exclude[d] += 1

    print(*(uft.size(i) - exclude[i] for i in range(n)))


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
