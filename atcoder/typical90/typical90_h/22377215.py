# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def atnum(s: str) -> int:
    if s == "a":
        return 0
    elif s == "t":
        return 1
    elif s == "c":
        return 2
    elif s == "o":
        return 3
    elif s == "d":
        return 4
    elif s == "e":
        return 5
    elif s == "r":
        return 6
    else:
        return -1


def main() -> None:
    n = int(sinput())
    s = sinput().strip()

    dp = [[0] * 7 for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(7):
            dp[i][j] = dp[i - 1][j]
        c = atnum(s[i - 1])
        if c == 0:
            dp[i][0] += 1
        elif c == -1:
            continue
        else:
            dp[i][c] += dp[i][c - 1]
            dp[i][c] %= MOD

    print(dp[-1][-1])


if __name__ == "__main__":
    main()
