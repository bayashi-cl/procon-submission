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
    n, l = map(int, readline().split())
    x = set(map(int, readline().split()))
    t = tuple(map(int, readline().split()))
    dp = [IINF] * (l + 1)
    dp[0] = 0
    for now in range(l):
        if now + 1 <= l:
            to = now + 1
            delay = t[2] if to in x else 0
            dp[to] = min(dp[to], dp[now] + t[0] + delay)
        if now + 2 <= l:
            to = now + 2
            delay = t[2] if to in x else 0
            dp[to] = min(dp[to], dp[now] + t[0] + t[1] + delay)
        if now + 4 <= l:
            to = now + 4
            delay = t[2] if to in x else 0
            dp[to] = min(dp[to], dp[now] + t[0] + 3 * t[1] + delay)

    ans = dp[l]
    for d in range(1, 4):
        if l - d >= 0:
            ans = min(ans, dp[l - d] + t[0] // 2 + t[1] // 2 + t[1] * (d - 1))
    print(ans)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
