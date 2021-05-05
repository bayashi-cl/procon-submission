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
    n, l = map(int, sinput().split())
    k = int(sinput())
    a = list(map(int, sinput().split()))

    diff = np.diff([0] + a + [l])
    ok = 0
    ng = l

    def is_ok(mid) -> bool:
        sum = 0
        cnt = 0
        for d in diff:
            sum += d
            if sum >= mid:
                cnt += 1
                sum = 0

        if cnt >= k + 1:
            return True
        else:
            return False

    while abs(ok - ng) > 1:
        mid = (ok + ng) // 2
        if is_ok(mid):
            ok = mid
        else:
            ng = mid

    print(ok)


if __name__ == "__main__":
    main()
