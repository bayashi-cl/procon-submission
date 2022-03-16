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
# from byslib.core.const import IINF, MOD, MOD7
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
MOD7 = byslib.core.const.MOD7
# from byslib.core.fastio import debug, readline, sinput
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

debug = byslib.core.fastio.debug
readline = byslib.core.fastio.readline
sinput = byslib.core.fastio.sinput
# from byslib.math.mod_comb import MultiComb
byslib.math = ModuleType("byslib.math")
byslib.math.mod_comb = ModuleType("byslib.math.mod_comb")

_code_byslib_math = """

"""
exec(_code_byslib_math, byslib.math.__dict__)

_code_byslib_math_mod_comb = """
class MultiComb:
    \"""二項係数
    **__init__: O(n)**
    **comb: O(1)**
    \"""

    def __init__(self, n: int, mod: int = 10**9 + 7) -> None:
        self.n = n
        self.mod = mod
        self.fact = [1, 1]
        self.factinv = [1, 1]
        self.inv = [0, 1]
        for i in range(2, self.n + 1):
            self.fact.append((self.fact[-1] * i) % self.mod)
            self.inv.append((-self.inv[self.mod % i] * (self.mod // i)) % self.mod)
            self.factinv.append((self.factinv[-1] * self.inv[-1]) % self.mod)

    def comb(self, n: int, r: int) -> int:
        if r < 0 or n < r:
            return 0
        r = min(r, n - r)
        return self.fact[n] * self.factinv[r] * self.factinv[n - r] % self.mod

    def perm(self, n: int, r: int) -> int:
        if r < 0 or n < r:
            return 0
        return self.fact[n] * self.factinv[n - r] % self.mod

    def hom(self, n: int, r: int) -> int:
        if n == r == 0:
            return 1
        return self.comb(n + r - 1, r)


def mono_comb(n: int, r: int, mod: int = 10**9 + 7) -> int:
    \"""二項係数
    **O(min(r, n-r))**
    python3.8 or later
    \"""
    r = min(r, n - r)
    numer = 1
    denom = 1
    for i in range(r):
        numer *= n - i
        denom *= r - i

        numer %= mod
        denom %= mod

    denom_mod = pow(denom, -1, mod)
    return (numer * denom_mod) % mod
"""
exec(_code_byslib_math_mod_comb, byslib.math.mod_comb.__dict__)

MultiComb = byslib.math.mod_comb.MultiComb


@procon_setup
def main(**kwargs) -> None:
    n, k = map(int, readline().split())
    a = list(map(int, readline().split()))
    a.sort()
    mc = MultiComb(n)
    ans = 0

    for i, ai in enumerate(a):
        ans += mc.comb(i, k - 1) * ai % MOD7
    a.sort(reverse=True)
    for i, ai in enumerate(a):
        ans -= mc.comb(i, k - 1) * ai % MOD7
    print(ans % MOD7)


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
