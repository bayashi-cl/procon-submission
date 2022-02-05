import functools
import sys
import typing
from math import log2
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    if 2 <= n <= 4:
        print("No")
    else:
        print("Yes")


if __name__ == "__main__":
    main()
