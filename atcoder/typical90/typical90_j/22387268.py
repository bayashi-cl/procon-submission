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
    n = int(sinput())
    cs1 = [0] * (n + 1)
    cs2 = [0] * (n + 1)
    for i in range(1, n + 1):
        c, p = map(int, sinput().split())
        cs1[i] = cs1[i - 1]
        cs2[i] = cs2[i - 1]
        if c == 1:
            cs1[i] += p
        elif c == 2:
            cs2[i] += p
        else:
            raise ValueError

    q = int(input())
    for _ in range(q):
        l, r = map(int, sinput().split())
        ans1 = cs1[r] - cs1[l - 1]
        ans2 = cs2[r] - cs2[l - 1]

        print(ans1, ans2)


if __name__ == "__main__":
    main()
