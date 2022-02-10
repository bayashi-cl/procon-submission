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
    a, b, c = map(int, sinput().split())
    k = int(sinput())
    cnt = 0
    while a >= b:
        b *= 2
        cnt += 1

    while b >= c:
        c *= 2
        cnt += 1

    print("Yes" if cnt <= k else "No")


if __name__ == "__main__":
    main()
