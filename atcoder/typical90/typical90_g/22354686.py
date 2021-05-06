# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
from bisect import bisect


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    q = int(sinput())

    a.sort()

    for _ in range(q):
        b = int(sinput())
        i = bisect(a, b)
        try:
            res = abs(a[i] - b)
        except IndexError:
            res = INF
        try:
            res = min(res, abs(a[i - 1] - b))
        except IndexError:
            pass
        print(res)


if __name__ == "__main__":
    main()
