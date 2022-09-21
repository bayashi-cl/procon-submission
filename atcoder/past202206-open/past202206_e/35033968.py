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

from .fastio import readable


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

        if readable():
            print("🔺 Unused inputs.", file=sys.stderr)

    return wrapper
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

if "USER" in os.environ:
    import inspect

    stdin = sys.stdin.buffer

    def debug(*args, sep: str = " ") -> None:
        line = inspect.getouterframes(inspect.currentframe())[1].lineno
        header = f"📌 line{line:>4}: "
        space = "\\n" + " " * (len(header) + 1)
        out = header + sep.join(map(str, args)).replace("\\n", space)
        print(out, file=sys.stderr)

else:
    stdin = io.BytesIO(os.read(0, os.fstat(0).st_size))

    def debug(*args, sep: str = " ") -> None:
        pass


readline = stdin.readline


def readable() -> bool:
    return len(stdin.read()) != 0


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: Union[str, bytes]) -> int:
    return int(s) - 1
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
    fullname="byslib.utility",
    is_package=True,
    code="""\
""",
)

BundleImporter.add_module(
    fullname="byslib.utility.binary_search",
    is_package=False,
    code="""\
# @title Binary search
from typing import Callable


def meguru_bisect(ok: int, ng: int, is_ok: Callable[..., bool], *args) -> int:
    \"""Binary Search

    Parameters
    ----------
    ok
        Inital value s.t. is_ok(ok) == True
    ng
        Inital value s.t. is_ok(ng) == False
    is_ok
        Judge function

    Returns
    -------
        number of is_ok(x) == True and is_ok(x ± 1) == False

    Notes
    -----
    Time complexity

    O(log(abs(ok-ng)))

    References
    ----------
    ..[1] https://twitter.com/meguru_comp/status/697008509376835584

    Examples
    --------
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


def bisect_float(
    ok: float, ng: float, rep: int, is_ok: Callable[..., bool], *args
) -> float:
    assert is_ok(ok, *args)
    assert not is_ok(ng, *args)
    for _ in range(rep):
        mid = (ok + ng) / 2
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok
""",
)

sys.meta_path.append(BundleImporter)

from byslib.core.config import procon_setup
from byslib.core.const import IINF, MOD
from byslib.core.fastio import debug, int1, readline, sinput
from byslib.utility.binary_search import meguru_bisect


@procon_setup
def main(**kwargs) -> None:
    n = int1(readline())

    loop = meguru_bisect(0, 10**10, lambda x: x**2 + x <= n)
    r = n - (loop**2 + loop)

    if r <= loop + 1:
        print(r + 1)
    else:
        e = r - loop - 1
        print((loop + 2) - e)


if __name__ == "__main__":
    t = 1  # * int(readline())
    main(t)

# package infomations
# -----------------------------------------------------------------------------
# byslib-python
#   Version  : 0.1.0
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# -----------------------------------------------------------------------------
