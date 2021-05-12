# region template
from __future__ import annotations

import sys
from typing import Callable, Final

import numpy as np
import numpy.linalg as LA

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    t = int(sinput())  # time
    l, x, y = map(int, sinput().split())  # height/target
    r = l / 2

    def solve(e: int) -> float:
        azi = 360 * e / t
        pol = (630 - azi) % 360
        theta = np.deg2rad(pol)
        pos = np.array([0, np.cos(theta) * r])
        dis = LA.norm(pos - np.array([x, y]))
        height = np.sin(theta) * r + r
        dip = np.arctan2(height, dis)
        res = np.degrees(dip)
        return res

    q = int(sinput())
    for _ in range(q):
        e = int(sinput())
        ans = solve(e)
        print(f"{ans:.10f}")


if __name__ == "__main__":
    main()
