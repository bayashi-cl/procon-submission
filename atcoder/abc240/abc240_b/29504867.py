import sys

# from byslib.core import IINF, MOD, debug, sinput
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")
byslib.core.io = ModuleType("byslib.core.io")

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

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

_code_byslib_core_io = """
import sys
from functools import partial


def sinput() -> str:
    return sys.stdin.readline().rstrip("\\r\\n")


def int1(s: str) -> int:
    return int(s) - 1


debug = partial(print, file=sys.stderr)
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

_code_byslib_core = """
# from .const import MOD, MOD7, INF, IINF
# from .io import debug, int1, sinput
"""
byslib.core.__dict__["MOD"] = byslib.core.const.MOD
byslib.core.__dict__["MOD7"] = byslib.core.const.MOD7
byslib.core.__dict__["INF"] = byslib.core.const.INF
byslib.core.__dict__["IINF"] = byslib.core.const.IINF
byslib.core.__dict__["debug"] = byslib.core.io.debug
byslib.core.__dict__["int1"] = byslib.core.io.int1
byslib.core.__dict__["sinput"] = byslib.core.io.sinput
exec(_code_byslib_core, byslib.core.__dict__)

IINF = byslib.core.IINF
MOD = byslib.core.MOD
debug = byslib.core.debug
sinput = byslib.core.sinput


def main() -> None:
    n = int(sinput())
    a = set(map(int, sinput().split()))
    print(len(a))


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
