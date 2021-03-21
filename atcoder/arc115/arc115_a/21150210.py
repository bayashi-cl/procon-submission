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
    N, M = map(int, sinput().split())
    g = 0
    k = 0
    for _ in range(N):
        s = sinput().strip().count("1")
        if s % 2 == 0:
            g += 1
        else:
            k += 1
    print(g * k)


if __name__ == "__main__":
    main()
