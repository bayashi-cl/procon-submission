import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def f(x):
    return x ** 2 + 2 * x + 3


def main() -> None:
    t = int(sinput())
    print(f(f(f(t) + t) + f(f(t))))


if __name__ == "__main__":
    main()
