# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    n, k = map(int, sinput().split())

    for i in range(k):
        if n % 200 == 0:
            n = n // 200
        else:
            n = n * 1000 + 200
    print(n)


if __name__ == "__main__":
    main()
