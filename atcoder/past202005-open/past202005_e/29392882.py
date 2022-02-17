import sys

# region from byslib.core.const import IINF, INF, MOD, MOD7
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")

_code_byslib = """
# procon library

__version__ = "0.0.1"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core = """
# core
"""
exec(_code_byslib_core, byslib.core.__dict__)

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

IINF = byslib.core.const.IINF
INF = byslib.core.const.INF
MOD = byslib.core.const.MOD
MOD7 = byslib.core.const.MOD7
# endregion
# region from byslib.core.io import debug, int1, sinput
byslib.core.io = ModuleType("byslib.core.io")

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

debug = byslib.core.io.debug
int1 = byslib.core.io.int1
sinput = byslib.core.io.sinput
# endregion


def main() -> None:
    n, m, q = map(int, sinput().split())
    graph = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int1, sinput().split())
        graph[u].append(v)
        graph[v].append(u)

    c = list(map(int, sinput().split()))
    for _ in range(q):
        t, *com = map(int, sinput().split())
        if t == 1:
            (x,) = com
            x -= 1
            print(c[x])
            for nxt in graph[x]:
                c[nxt] = c[x]
        else:
            x, y = com
            x -= 1
            print(c[x])
            c[x] = y


if __name__ == "__main__":
    sys.setrecursionlimit(10 ** 6)
    main()
