# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final

import numpy as np

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    N = int(sinput())
    p0 = np.array(list(map(int, sinput().split())))
    p1 = np.array(list(map(int, sinput().split())))

    m = (p0 + p1) / 2
    theta = 2 * np.pi / N
    rot_mat = np.array(
        [[np.cos(theta), -np.sin(theta)], [np.sin(theta), np.cos(theta)]]
    )
    ans = (rot_mat @ (p0 - m)) + m
    print(*ans)


if __name__ == "__main__":
    main()
