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
# from byslib.core.io import debug, readline, sinput, int1
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
int1 = byslib.core.io.int1


def main() -> None:
    n, m = map(int, readline().split())
    a = [0] * m
    c = [0] * m
    for i in range(m):
        ai, _ = map(int, readline().split())
        a[i] = ai
        ci = 0
        for cij in map(int1, readline().split()):
            ci |= 1 << cij
        c[i] = ci

    dp = [[IINF] * (1 << n) for _ in range(m + 1)]
    dp[0][0] = 0

    for i, (ci, ai) in enumerate(zip(c, a)):
        for j in range(1 << n):
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j])
            dp[i + 1][j | ci] = min(dp[i + 1][j | ci], dp[i][j] + ai)

    print(-1 if dp[-1][-1] == IINF else dp[-1][-1])


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
