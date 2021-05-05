# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final

from functools import lru_cache

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(input())
    if n % 2 == 1:
        return

    @lru_cache
    def knit(l: int) -> set[str]:
        if l == 2:
            return {"()"}
        res: set[str] = set()
        one = knit(l - 2)
        for o in one:
            res.add("(" + o + ")")

        for i in range(2, l, 2):
            two_left = knit(i)
            two_right = knit(l - i)
            for tl in two_left:
                for tr in two_right:
                    res.add(tl + tr)

        return res

    ans = list(knit(n))
    ans.sort()

    print("\n".join(ans))


if __name__ == "__main__":
    main()
