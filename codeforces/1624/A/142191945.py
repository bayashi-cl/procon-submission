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


def main() -> None:
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    print(max(a) - min(a))


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
