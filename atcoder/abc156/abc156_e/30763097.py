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
# from byslib.numeric.mod_comb import MultiComb
byslib.numeric = ModuleType("byslib.numeric")
byslib.numeric.mod_comb = ModuleType("byslib.numeric.mod_comb")

_code_byslib_numeric = """

"""
exec(_code_byslib_numeric, byslib.numeric.__dict__)

_code_byslib_numeric_mod_comb = """
# @title Binomial coefficient
class MultiComb:
    \"""Binomial coefficient

    Notes
    -----
    Time complexity

    * construct: O(n)
    * query: O(1)

    References
    ----------
    ..[1] https://drken1215.hatenablog.com/entry/2018/06/08/210000

    Examples
    --------
    >>> mc = MultiComb(10)
    >>> print(mc.comb(5, 3))
    10
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
        \"""nCr\"""
        if r < 0 or n < r:
            return 0
        r = min(r, n - r)
        return self.fact[n] * self.factinv[r] * self.factinv[n - r] % self.mod

    def perm(self, n: int, r: int) -> int:
        \"""nPr\"""
        if r < 0 or n < r:
            return 0
        return self.fact[n] * self.factinv[n - r] % self.mod

    def hom(self, n: int, r: int) -> int:
        \"""nHr\"""
        if n == r == 0:
            return 1
        return self.comb(n + r - 1, r)


def mono_comb(n: int, r: int, mod: int = 10**9 + 7) -> int:
    \"""_summary_

    Parameters
    ----------
    n
        n
    r
        r
    mod, optional
        mod, by default 10**9+7

    Returns
    -------
        nCr

    Notes
    -----
    Time complexity

    O(min(r, n - r))

    Examples
    --------
    Examples
    --------
    >>> print(mono_comb(5, 3))
    10
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
exec(_code_byslib_numeric_mod_comb, byslib.numeric.mod_comb.__dict__)

MultiComb = byslib.numeric.mod_comb.MultiComb
# from byslib.numeric.modint import using_modint
byslib.numeric.modint = ModuleType("byslib.numeric.modint")

_code_byslib_numeric_modint = """
# @title Modint
from typing import Union


class modint:
    \"""Modint
    Not so fast.
    \"""

    __slots__ = ("v",)
    mod: int = 0

    def __init__(self, v: int = 0) -> None:
        self.v = v % self.mod

    def __repr__(self):
        return str(self.v)

    def __index__(self):
        return self.v

    def __iadd__(self, other: Union["modint", int]) -> "modint":
        if isinstance(other, int):
            self.v += other
        else:
            self.v += other.v

        self.v %= self.mod
        return self

    def __isub__(self, other: Union["modint", int]) -> "modint":
        if isinstance(other, int):
            self.v -= other
        else:
            self.v -= other.v

        self.v %= self.mod
        return self

    def __imul__(self, other: Union["modint", int]) -> "modint":
        if isinstance(other, int):
            self.v *= other
        else:
            self.v *= other.v

        self.v %= self.mod
        return self

    def __ipow__(self, other: int) -> "modint":
        self.v = pow(self.v, other, self.mod)
        return self

    def __ifloordiv__(self, other: Union["modint", int]) -> "modint":
        if isinstance(other, int):
            self.v *= pow(other, self.mod - 2, self.mod)
        else:
            self.v *= pow(other.v, self.mod - 2, self.mod)

        self.v %= self.mod
        return self

    def __add__(self, other: Union["modint", int]) -> "modint":
        res = self.__class__(self.v)
        res += other
        return res

    def __sub__(self, other: Union["modint", int]) -> "modint":
        res = self.__class__(self.v)
        res -= other
        return res

    def __mul__(self, other: Union["modint", int]) -> "modint":
        res = self.__class__(self.v)
        res *= other
        return res

    def __floordiv__(self, other: Union["modint", int]) -> "modint":
        res = self.__class__(self.v)
        res //= other
        return res

    def __pow__(self, other: int) -> "modint":
        res = self.__class__(self.v)
        res **= other
        return res

    def inv(self) -> "modint":
        return self.__class__(pow(self.v, self.mod - 2, self.mod))

    def __radd__(self, other: int) -> "modint":
        res = self.__class__(other)
        res += self
        return res

    def __rsub__(self, other: int) -> "modint":
        res = self.__class__(other)
        res -= self
        return res

    def __rmul__(self, other: int) -> "modint":
        res = self.__class__(other)
        res *= self
        return res

    def __rfloordiv__(self, other: int) -> "modint":
        res = self.__class__(other)
        res //= self
        return res


def using_modint(modulo: int):
    \"""using modint

    set modulo to modint class

    Parameters
    ----------
    modulo

    Returns
    -------
        modint class mod = modulo
    \"""

    class Mint(modint):
        __slots__ = ()
        mod: int = modulo

    return Mint


modint998244353 = using_modint(998244353)
modint1000000007 = using_modint(1000000007)
"""
exec(_code_byslib_numeric_modint, byslib.numeric.modint.__dict__)

using_modint = byslib.numeric.modint.using_modint


@procon_setup
def main(**kwargs) -> None:
    n, k = map(int, readline().split())
    mc = MultiComb(n)
    mint = using_modint(MOD7)
    ans = mint()
    for i in range(n, max(n - k - 1, 0), -1):
        ans += mc.comb(n, i) * mc.comb(n - 1, i - 1)

    print(ans)


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
