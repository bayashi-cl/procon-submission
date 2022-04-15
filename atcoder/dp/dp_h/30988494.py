import sys

if sys.argv[-1] == "ONLINE_JUDGE":
    import textwrap
    import pathlib

    import numpy as np
    from Cython.Build import cythonize
    from setuptools import Extension, setup

    file = pathlib.Path("byslib/__init__.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    \"""
    procon library by bayashi-cl
    github repository: https://github.com/bayashi-cl/byslib-python

    This library can be expanded with expander.
     - https://github.com/bayashi-cl/expander
    \"""

    __version__ = "0.0.2"
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("byslib/core/__init__.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("byslib/core/config.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    import sys
    from typing import Callable


    def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
        sys.setrecursionlimit(10**7)

        def wrapper(case: int = 1) -> None:
            for i in range(case):
                main(case=i + 1)

        return wrapper
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("byslib/core/const.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    import sys

    MOD: int = 998244353
    MOD7: int = 1000000007
    INF: float = float("Inf")
    IINF: int = sys.maxsize // 2
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("byslib/core/fastio.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
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
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("cyslib/__init__.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("cyslib/numeric/__init__.py")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    """
    file.write_text(textwrap.dedent(code))

    file = pathlib.Path("cyslib/numeric/modint.pyx")
    file.parent.mkdir(parents=True, exist_ok=True)
    code = """\
    # distutils: language=c++
    # cython: language_level=3, boundscheck=False, wraparound=False, cdivision=True

    cdef unsigned int mod[1]
    mod[0] = 0

    def set_mod(unsigned int modulo):
        assert modulo < 2**31
        mod[0] = modulo

    cdef unsigned int floor_mod(long long int v):
        cdef int res = v % mod[0]
        if res < 0:
            res += mod[0]
        return res

    cdef class Modint:
        cdef public unsigned int v

        def __cinit__(Modint self, long long int v = 0):
            self.v = floor_mod(v)

        def __iadd__(Modint self, other):
            if isinstance(other, Modint):
                self.v += other.v
            else:
                self.v += floor_mod(other)

            if self.v >= mod[0]:
                self.v -= mod[0]
            return self

        def __isub__(Modint self, other):
            cdef unsigned int uother = other.v if isinstance(other, Modint) else floor_mod(other)
            if self.v < uother:
                self.v += mod[0]

            self.v -= uother
            return self

        def __imul__(Modint self, other):
            cdef unsigned long long z = self.v
            if isinstance(other, Modint):
                z *= other.v
            else:
                z *= floor_mod(other)

            self.v = floor_mod(z)
            return self

        def __ifloordiv__(Modint self, other):
            cdef unsigned long long z = self.v
            if isinstance(other, Modint):
                z *= pow(other.v, mod[0] - 2, mod[0])
            else:
                z *= pow(floor_mod(other), mod[0] - 2, mod[0])

            self.v = floor_mod(z)
            return self

        def __add__(Modint self, other):
            cdef Modint res = Modint(self.v)
            res += other
            return res

        def __sub__(Modint self, other):
            cdef Modint res = Modint(self.v)
            res -= other
            return res

        def __mul__(Modint self, other):
            cdef Modint res = Modint(self.v)
            res *= other
            return res

        def __floordiv__(Modint self, other):
            cdef Modint res = Modint(self.v)
            res //= other
            return res

        @property
        def val(Modint self):
            return self.v

        cpdef inv(Modint self):
            return Modint(pow(self.v, mod[0] - 2, mod[0]))

        cpdef pow(Modint self, int p):
            return Modint(pow(self.v, p, mod[0]))

        def __neg__(Modint self):
            cdef long long int x = self.v
            return Modint(-x)

        def __repr__(Modint self):
            return f"{self.v}"

        def __eq__(Modint self, Modint other):
            return self.v == other.v

        def __ne__(Modint self, Modint other):
            return self.v != other.v
    """
    file.write_text(textwrap.dedent(code))

    extensions = Extension(
        "*",
        ["./**/*.pyx"],
        include_dirs=[np.get_include()],
        extra_compile_args=["-O3"],
    )
    setup(
        ext_modules=cythonize([extensions]),
        script_args=["build_ext", "--inplace"],
    )

from byslib.core.config import procon_setup
from byslib.core.const import MOD7
from byslib.core.fastio import readline, sinput
from cyslib.numeric.modint import Modint, set_mod


@procon_setup
def main(**kwargs) -> None:
    set_mod(MOD7)
    h, w = map(int, readline().split())
    a = [sinput() for _ in range(h)]
    dp = [[Modint() for _ in range(w)] for _ in range(h)]
    dp[0][0] += Modint(1)
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
# -----------------------------------------------------------------------------
# byslib-python
#   Version  : 0.0.2
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# -----------------------------------------------------------------------------
# byslib-cython
#   Version  : 0.0.1
#   Author   : bayashi-cl
#   License  : CC0
# -----------------------------------------------------------------------------
