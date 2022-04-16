import os
import sys
from importlib.machinery import ModuleSpec, SourceFileLoader


class BundleImporter(SourceFileLoader):
    """Importer that supports importing from strings in code.

    This class is automatically generated by expander.
    """

    module_ispkg = dict()
    module_code = dict()

    @classmethod
    def add_module(cls, fullname, is_package, code):
        cls.module_ispkg[fullname] = is_package
        cls.module_code[cls.get_filename(fullname)] = bytes(code, encoding="utf-8")

    @classmethod
    def find_spec(cls, fullname, path=None, target=None):
        if fullname in cls.module_ispkg:
            return ModuleSpec(
                fullname,
                cls(fullname, ""),
                is_package=cls.module_ispkg[fullname],
            )
        else:
            return None

    @classmethod
    def get_filename(cls, fullname):
        return fullname.replace(".", "_") + ".py"

    def get_data(self, path):
        try:
            return super().get_data(path)
        except OSError:
            try:
                return self.module_code[path]
            except KeyError:
                raise OSError

    def path_stats(self, path):
        return {"mtime": os.stat(__file__).st_mtime, "size": None}


BundleImporter.add_module(
    fullname="byslib",
    is_package=True,
    code="""\
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.2"
""",
)

BundleImporter.add_module(
    fullname="byslib.core",
    is_package=True,
    code="""\
""",
)

BundleImporter.add_module(
    fullname="byslib.core.config",
    is_package=False,
    code="""\
import sys
from typing import Callable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    sys.setrecursionlimit(10**7)

    def wrapper(case: int = 1) -> None:
        for i in range(case):
            main(case=i + 1)

    return wrapper
""",
)

BundleImporter.add_module(
    fullname="byslib.core.const",
    is_package=False,
    code="""\
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
""",
)

BundleImporter.add_module(
    fullname="byslib.core.fastio",
    is_package=False,
    code="""\
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
""",
)

BundleImporter.add_module(
    fullname="byslib.numeric",
    is_package=True,
    code="""\
""",
)

BundleImporter.add_module(
    fullname="byslib.numeric.modarray",
    is_package=False,
    code="""\
# @title Modarray
from array import array


def using_modarray(modulo: int):
    \"""Set modulo to modarray class.


    Parameters
    ----------
    modulo

    Returns
    -------
        modarray class mod is modulo
    \"""

    class ModArray(array):
        \"""Mod Array
        Take a mod for every assignment.
        \"""

        __slots__ = ()
        mod: int = modulo

        @classmethod
        def zeros(cls, n: int) -> "ModArray":
            return cls("L", [0] * n)

        def __setitem__(self, index, value) -> None:
            super().__setitem__(index, value % self.mod)

        def inv(self, index: int) -> int:
            return pow(self[index], self.mod - 2, self.mod)

    return ModArray


modarray998244353 = using_modarray(998244353)
modarray1000000007 = using_modarray(1000000007)
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, readline, sinput
from byslib.numeric.modarray import modarray998244353 as marr


@procon_setup
def main(**kwargs) -> None:
    n, m, k = map(int, readline().split())
    dp = [marr.zeros(k + 1) for _ in range(n + 1)]
    dp[0][0] = 1
    for i in range(1, n + 1):
        for j in range(k + 1):
            for ai in range(1, m + 1):
                if j - ai >= 0:
                    dp[i][j] += dp[i - 1][j - ai]

    print(sum(dp[n]) % MOD)


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
