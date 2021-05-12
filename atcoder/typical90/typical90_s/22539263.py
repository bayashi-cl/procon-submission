# region template
import sys
from typing import Callable
from functools import lru_cache

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: int = sys.maxsize
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))

    @lru_cache(maxsize=None)
    def dp(l: int, r: int) -> int:
        # [l, r]
        assert l <= r

        if r - l == 1:
            return abs(a[r] - a[l])

        res = INF
        res = min(res, dp(l + 1, r - 1) + abs(a[l] - a[r]))

        for m in range(l + 1, r - 1, 2):
            res = min(res, dp(l, m) + dp(m + 1, r))
        return res

    print(dp(0, 2 * n - 1))


if __name__ == "__main__":
    main()
