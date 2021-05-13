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
    n = int(sinput())
    plane = np.zeros((1001, 1001))
    for _ in range(n):
        lx, ly, rx, ry = map(int, sinput().split())
        plane[lx, ly] += 1
        plane[rx, ry] += 1
        plane[rx, ly] -= 1
        plane[lx, ry] -= 1

    cs = np.cumsum(plane, axis=1)
    cs = np.cumsum(cs, axis=0)

    uni, count = np.unique(cs, return_counts=True)
    asort = np.argsort(uni)
    uni = uni[asort]
    count = count[asort]

    k = 1
    for u, c in zip(uni, count):
        if u == 0:
            continue
        while True:
            if k == u:
                print(c)
                k += 1
                break
            else:
                print(0)
                k += 1
    else:
        while k <= n:
            print(0)
            k += 1


if __name__ == "__main__":
    main()
