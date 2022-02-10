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
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    for i in range(n - k):
        if a[i] < a[i + k]:
            print("Yes")
        else:
            print("No")


if __name__ == "__main__":
    main()
