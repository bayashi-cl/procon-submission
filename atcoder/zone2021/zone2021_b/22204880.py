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
    n, D, H = map(int, sinput().split())
    ans = 0
    for _ in range(n):
        d, h = map(int, sinput().split())
        a = (H - h) / (D - d)
        b = H - a * D
        ans = max(ans, b)

    print(ans)


if __name__ == "__main__":
    main()
