import sys
from array import array

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

if sys.argv[-1] == "ONLINE_JUDGE":
    import subprocess

    code = """
# distutils: language=c++
# cython: language_level=3, boundscheck=False, wraparound=False, cdivision=True
cimport cython

ctypedef unsigned long long u8
ctypedef long long int i8
ctypedef unsigned int u4

cdef u4 mod_context[1]
mod_context[0] = 0

def set_mod(u4 modulo):
    mod_context[0] = modulo
cdef mod():
    return mod_context[0]

cdef class Modint:
    cdef public u4 v

    def __init__(Modint self, i8 v = 0):
        cdef i8 x = v % mod()
        if x < 0:
            x += mod()
        self.v = x

    def __repr__(Modint self):
        return f"{self.v}"

    def __iadd__(Modint self, other):
        if isinstance(other, Modint):
            self.v += other.v
        else:
            self.v += Modint(other).v

        if self.v >= mod():
            self.v %= mod()
        return self

    def __add__(Modint self, other):
        cdef Modint res = Modint(self.v)
        res += other
        return res

"""
    open("modint.pyx", "w").write(code)
    subprocess.run(["cythonize", "-i", "-3", "-b", "**/*.pyx"])

from modint import Modint, set_mod


@procon_setup
def main(**kwargs) -> None:
    # marr = using_modarray(1000000007)
    set_mod(MOD7)
    h, w = map(int, readline().split())
    a = [sinput() for _ in range(h)]
    dp = [[Modint() for _ in range(w)] for _ in range(h)]
    # dp = [[0] * w for _ in range(h)]
    dp[0][0] += 1
    for i in range(h):
        for j in range(w):
            if a[i][j] == "#":
                continue
            if i + 1 != h and a[i + 1][j] == ".":
                dp[i + 1][j] += dp[i][j]
                # dp[i + 1][j] %= MOD7
            if j + 1 != w and a[i][j + 1] == ".":
                dp[i][j + 1] += dp[i][j]
                # dp[i][j + 1] %= MOD7

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
