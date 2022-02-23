import sys

# from byslib.core.const import IINF, MOD, MOD7
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
MOD7 = byslib.core.const.MOD7
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

    def __init__(self, n: int, mod: int = 10 ** 9 + 7) -> None:
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
        if (r < 0) or (n < r):
            return 0
        r = min(r, n - r)
        return self.fact[n] * self.factinv[r] * self.factinv[n - r] % self.mod


def mono_comb(n: int, r: int, mod: int = 10 ** 9 + 7) -> int:
    \"""二項係数
    **O(r)**
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


def main() -> None:
    n, m, k = map(int, readline().split())
    mc = MultiComb(n * m, MOD7)
    ans = 0
    for h in range(1, n):
        cnt = m * m * (n - h) % MOD7 * mc.comb(n * m - 2, k - 2) % MOD7
        ans += cnt * h % MOD7
        ans %= MOD7

    for w in range(1, m):
        cnt = n * n * (m - w) % MOD7 * mc.comb(n * m - 2, k - 2) % MOD7
        ans += cnt * w % MOD7
        ans %= MOD7

    print(ans)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
