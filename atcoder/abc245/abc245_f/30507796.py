import numpy as np
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
# from byslib.core.fastio import readline
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

readline = byslib.core.fastio.readline
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import connected_components


@procon_setup
def main(**kwargs) -> None:
    n, m = map(int, readline().split())
    if m == 0:
        print(0)
        return
    edge = np.array([readline().split() for _ in range(m)], dtype=np.int32).T - 1
    cost = np.ones(m, dtype=np.int32).T
    graph = csr_matrix((cost, edge), (n, n))
    inv = csr_matrix((cost, edge[::-1]), (n, n)).tolil()
    _, scc = connected_components(graph, directed=True, connection="strong")
    dp = np.array([False] * n)
    _, cnt = np.unique(scc, return_counts=True)
    arg = np.argsort(scc)
    dp[arg[cnt[scc[arg]] > 1]] = True
    for ar in arg:
        dp[inv.rows[ar]] |= dp[ar]
    print(sum(dp))


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
