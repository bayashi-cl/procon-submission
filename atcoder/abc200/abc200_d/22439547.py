# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final, Union
from copy import copy


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def ans(x_, y_):
    x = [xi + 1 for xi in x_]
    y = [yi + 1 for yi in y_]
    print("Yes")
    print(len(x), *x)
    print(len(y), *y)
    exit()


def main() -> None:
    n = int(sinput())
    a_ = list(map(int, sinput().split()))
    a = [ai % 200 for ai in a_]
    dp: list[list[Union[bool, list[int]]]] = [[False] * 200 for _ in range(n + 1)]
    dp[0][a[0]] = [0]

    for i in range(1, n):
        for k in range(200):
            if not dp[i][k]:
                dp[i][k] = dp[i - 1][k]

        if dp[i][a[i]]:
            ans(dp[i][a[i]], [i])
        else:
            dp[i][a[i]] = [i]

        for j in range(200):
            if dp[i][j]:
                if j == a[i]:
                    continue
                elif dp[i][(j + a[i]) % 200]:
                    ans(dp[i][j] + [i], dp[i][(j + a[i]) % 200])
                else:
                    dp[i + 1][(j + a[i]) % 200] = dp[i][j] + [i]

    else:
        print("No")


if __name__ == "__main__":
    main()
