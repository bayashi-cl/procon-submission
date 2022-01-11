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
    n = int(sinput())
    cnt = [0] * n
    for _ in range(n):
        ai = int(sinput())
        cnt[ai - 1] += 1
    try:
        f = cnt.index(0)
        t = cnt.index(2)
        print(t + 1, f + 1)
    except ValueError:
        print("Correct")


if __name__ == "__main__":
    main()
