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
# from byslib.numeric.modint import Mint7
byslib.numeric = ModuleType("byslib.numeric")
byslib.numeric.modint = ModuleType("byslib.numeric.modint")

_code_byslib_numeric = """

"""
exec(_code_byslib_numeric, byslib.numeric.__dict__)

_code_byslib_numeric_modint = """
from typing import Union


class modint:
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


def using_modint(m: int):
    class Mint(modint):
        __slots__ = ()
        mod: int = m

    return Mint


Mint = using_modint(998244353)
Mint7 = using_modint(1000000007)
"""
exec(_code_byslib_numeric_modint, byslib.numeric.modint.__dict__)

Mint7 = byslib.numeric.modint.Mint7


@procon_setup
def main(**kwargs) -> None:
    h, w = map(int, readline().split())
    a = [sinput() for _ in range(h)]
    dp = [[Mint7() for _ in range(w)] for _ in range(h)]
    dp[0][0] += 1
    for i in range(h):
        for j in range(w):
            if a[i][j] == "#":
                continue
            if i + 1 != h and a[i + 1][j] == ".":
                dp[i + 1][j] += dp[i][j]
            if j + 1 != w and a[i][j + 1] == ".":
                dp[i][j + 1] += dp[i][j]

    print(dp[-1][-1])


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
