# region template
from __future__ import annotations

import sys
from typing import Callable, Final

from math import gcd

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    a, b, c = map(int, sinput().split())
    n = gcd(gcd(a, b), c)
    ans = a // n + b // n + c // n - 3
    print(ans)


if __name__ == "__main__":
    main()
