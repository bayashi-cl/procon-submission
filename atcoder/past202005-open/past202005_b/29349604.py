from __future__ import annotations

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

# from __future__ import annotations
import sys

# from byslib.core.const import IINF, INF, MOD, MOD7
# from byslib.core.io import debug, int1, sinput


def main() -> None:
    N, M, Q = map(int, sinput().split())
    solve: list[set[int]] = [set() for _ in range(N)]
    point = [N] * M

    for _ in range(Q):
        t, *nm = map(int1, sinput().split())
        if t == 0:
            (n,) = nm
            ans = 0
            for p in solve[n]:
                ans += point[p]
            print(ans)
        else:
            n, m = nm
            point[m] -= 1
            solve[n].add(m)


if __name__ == "__main__":
    sys.setrecursionlimit(10 ** 6)
    main()
