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

__version__ = "0.1.0"
""",
)

BundleImporter.add_module(
    fullname="byslib.core",
    is_package=True,
    code="""\
# @title Core Featule
""",
)

BundleImporter.add_module(
    fullname="byslib.core.config",
    is_package=False,
    code="""\
# @title setup
import sys
from typing import Callable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    \"""setup

    Notes
    -----
    * Set recursionlimit to 1e7
    * Repeat main function for testcases
    * If exception raised, indicate in which test case it was raised.
    \"""

    def wrapper(case: int = 1) -> None:
        sys.setrecursionlimit(10**7)
        for i in range(case):
            try:
                main(case=i + 1)
            except Exception as e:
                print(
                    f"❌ {type(e).__name__} raised in tastcase {i + 1}.",
                    file=sys.stderr,
                )
                raise

    return wrapper
""",
)

BundleImporter.add_module(
    fullname="byslib.core.const",
    is_package=False,
    code="""\
# @title Const
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
# @title Fast I/O
import io
import os
import sys
from typing import Union

readline = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

if "USER" in os.environ:
    import inspect

    def debug(*args, sep: str = " ") -> None:
        line = inspect.getouterframes(inspect.currentframe())[1].lineno
        header = f"📌 line{line:>4}: "
        space = "\\n" + " " * (len(header) + 1)
        out = header + sep.join(map(str, args)).replace("\\n", space)
        print(out, file=sys.stderr)

else:

    def debug(*args, sep: str = " ") -> None:
        pass


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
    fullname="byslib.numeric.modint",
    is_package=False,
    code="""\
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
""",
)

sys.meta_path.append(BundleImporter)

from fractions import Fraction

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, readline, sinput
from byslib.numeric.modint import modint1000000007 as Mint


@procon_setup
def main(**kwargs) -> None:
    n, k = map(int, readline().split())
    a = list(map(int, readline().split()))

    a.sort(key=lambda x: abs(x), reverse=True)

    ans = Mint(1)
    neg_cnt = 0
    last_pos = -1
    last_neg = -1
    zero_flg = False
    for ai in a[:k]:
        ans *= ai
        if ai < 0:
            neg_cnt += 1
            last_neg = ai
        elif ai == 0:
            zero_flg = True
        elif ai > 0:
            last_pos = ai

    if neg_cnt % 2 == 0:
        print(ans)
    elif zero_flg:
        print(0)
    else:
        first_pos = -1
        first_neg = -1
        for ai in a[k:]:
            debug(ai)
            if ai >= 0 and first_pos == -1:
                first_pos = ai
            elif ai < 0:
                neg_cnt += 1
                if first_neg == -1:
                    first_neg = ai

        if neg_cnt == n:
            ans = Mint(1)
            a.reverse()
            for ai in a[:k]:
                ans *= ai
            print(ans)
        else:
            cand = []
            if first_pos != -1:
                cand.append((first_pos, last_neg))
            if last_pos != -1 and first_neg != -1:
                cand.append((first_neg, last_pos))

            if not cand:
                print(ans)
            else:
                num, den = min(cand, key=lambda nd: Fraction(*nd))
                print(ans * num // den)


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
