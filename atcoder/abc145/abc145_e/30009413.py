from operator import itemgetter

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
from typing import Callable, Optional


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    sys.setrecursionlimit(10**7)

    def wrapper(case: Optional[int] = None) -> None:
        if case is None:
            case = 1
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
import sys
from functools import partial

readline = sys.stdin.buffer.readline
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


@procon_setup
def main(**kwargs) -> None:
    n, t = map(int, readline().split())
    ab = [tuple(map(int, readline().split())) for _ in range(n)]
    ab.sort()
    dp = [[0] * (t + 3001) for _ in range(n + 1)]
    for i, (a, b) in enumerate(ab):
        for j in range(t + 3001):
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j])
            if j < t:
                dp[i + 1][j + a] = max(dp[i + 1][j + a], dp[i][j] + b)

    print(max(dp[-1]))


if __name__ == "__main__":
    t = None
    # t = int(readline())
    main(t)