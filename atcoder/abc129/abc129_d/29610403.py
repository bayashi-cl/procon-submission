import sys

# from byslib.core.const import IINF, MOD
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")

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
# from byslib.core.io import debug, readline, sinput
byslib.core.io = ModuleType("byslib.core.io")

_code_byslib_core_io = """
import sys
from functools import partial

readline = sys.stdin.buffer.readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: str) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

debug = byslib.core.io.debug
readline = byslib.core.io.readline
sinput = byslib.core.io.sinput


def main() -> None:
    h, w = map(int, readline().split())
    s = [sinput() + "#" for _ in range(h)]
    s.append("#" * (w + 1))

    cnt = [[0] * w for _ in range(h)]
    for i in range(h):
        l = -1
        for j in range(w + 1):
            c = s[i][j]
            if c == "#":
                if l != -1:
                    n = j - l
                    for k in range(l, j):
                        cnt[i][k] += n
                    l = -1
            else:
                if l == -1:
                    l = j

    for j in range(w):
        u = -1
        for i in range(h + 1):
            c = s[i][j]
            if c == "#":
                if u != -1:
                    n = i - u
                    for k in range(u, i):
                        cnt[k][j] += n
                    u = -1
            else:
                if u == -1:
                    u = i

    print(max(max(c) for c in cnt) - 1)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
