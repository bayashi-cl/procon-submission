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
    fullname="byslib.utility",
    is_package=True,
    code="""\
""",
)

BundleImporter.add_module(
    fullname="byslib.utility.grid",
    is_package=False,
    code="""\
import typing


class Grid:
    DeltaItr = typing.Iterable[typing.Tuple[int, int]]
    h: int
    w: int

    def __init__(self, h: int, w: int) -> None:
        self.h = h
        self.w = w

    def __contains__(self, ij: typing.Tuple[int, int]) -> bool:
        return 0 <= ij[0] < self.h and 0 <= ij[1] < self.w

    def area(self) -> int:
        return self.h * self.w

    def index(self, i: int, j: int) -> int:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        return self.w * i + j

    def coord(self, ind: int) -> typing.Tuple[int, int]:
        if ind < 0 or self.area() <= ind:
            raise ValueError("index out of grid")
        return divmod(ind, self.w)

    def delta(self, i: int, j: int, d: DeltaItr) -> DeltaItr:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        for di, dj in d:
            ni, nj = i + di, j + dj
            if (ni, nj) in self:
                yield (ni, nj)

    def delta2(self, i: int, j: int) -> DeltaItr:
        return self.delta(i, j, ((0, 1), (1, 0)))

    def delta4(self, i: int, j: int) -> DeltaItr:
        return self.delta(i, j, ((-1, 0), (0, 1), (1, 0), (0, -1)))

    def delta8(self, i: int, j: int) -> DeltaItr:
        d = []
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di == 0 and dj == 0:
                    continue
                d.append((di, dj))
        return self.delta(i, j, d)
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, int1, readline, sinput
from byslib.utility.grid import Grid


@procon_setup
def main(**kwargs) -> None:
    g = Grid(*map(int, readline().split()))
    r, c = map(int1, readline().split())
    print(len(list(g.delta4(r, c))))


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
