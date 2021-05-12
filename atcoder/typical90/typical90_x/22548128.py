# region template
from __future__ import annotations

import sys
from typing import Callable, Final

import numpy as np

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    b = list(map(int, sinput().split()))

    diff = 0
    for ai, bi in zip(a, b):
        diff += abs(ai - bi)

    if diff <= k and (k - diff) % 2 == 0:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
