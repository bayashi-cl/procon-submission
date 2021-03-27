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
    H, W, X, Y = map(int, sinput().split())
    S = list()
    for _ in range(H):
        S.append(sinput().strip())

    X -= 1
    Y -= 1
    ans = 1
    for i in range(1, 100):
        if X - i < 0 or X - i >= H:
            break
        if S[X - i][Y] == "#":
            break
        ans += 1
    for j in range(1, 100):
        if X + j < 0 or X + j >= H:
            break
        if S[X + j][Y] == "#":
            break
        ans += 1
    for k in range(1, 100):
        if Y - k < 0 or Y - k >= W:
            break
        if S[X][Y - k] == "#":
            break
        ans += 1
    for l in range(1, 100):
        if Y + l < 0 or Y + l >= W:
            break
        if S[X][Y + l] == "#":
            break
        ans += 1

    print(ans)


if __name__ == "__main__":
    main()
