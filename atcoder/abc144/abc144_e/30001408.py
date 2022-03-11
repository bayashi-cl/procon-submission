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
# from byslib.utility.binary_search import meguru_bisect
byslib.utility = ModuleType("byslib.utility")
byslib.utility.binary_search = ModuleType("byslib.utility.binary_search")

_code_byslib_utility = """

"""
exec(_code_byslib_utility, byslib.utility.__dict__)

_code_byslib_utility_binary_search = """
from typing import Callable


def meguru_bisect(ok: int, ng: int, is_ok: Callable[..., bool], *args) -> int:
    \"""二分探索法
    Args:
        ok (int): is_okを満たす初期値
        ng (int): is_okを満たさない初期値
        is_ok (typing.Callable[..., bool]): 判定用関数
        *args (object): is_okに渡される引数

    Returns:
        int: is_okを満たす最大/小の整数
    \"""
    assert is_ok(ok, *args)
    assert not is_ok(ng, *args)

    while abs(ok - ng) > 1:
        mid = (ok + ng) >> 1
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok
"""
exec(_code_byslib_utility_binary_search, byslib.utility.binary_search.__dict__)

meguru_bisect = byslib.utility.binary_search.meguru_bisect


def main() -> None:
    n, k = map(int, readline().split())
    a = list(map(int, readline().split()))
    f = list(map(int, readline().split()))
    a.sort()
    f.sort(reverse=True)

    def ok(x: int) -> bool:
        if x < 0:
            return False
        cnt = 0
        for ai, fi in zip(a, f):
            ea = x // fi
            cnt += max(ai - ea, 0)
        return cnt <= k

    print(meguru_bisect(IINF, -1, ok))


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
