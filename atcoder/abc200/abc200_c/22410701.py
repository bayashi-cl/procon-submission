# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
from collections import Counter


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    _ = int(sinput())
    a = list(map(int, sinput().split()))

    ans = 0.0
    m = [ai % 200 for ai in a]
    c = Counter(m)
    for v in c.values():
        ans += v * (v - 1) / 2

    print(int(ans))


if __name__ == "__main__":
    main()
