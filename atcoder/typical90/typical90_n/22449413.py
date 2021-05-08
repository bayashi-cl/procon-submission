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
    _ = sinput()
    a = list(map(int, sinput().split()))
    b = list(map(int, sinput().split()))
    a.sort()
    b.sort()
    ans = 0
    for ai, bi in zip(a, b):
        ans += abs(ai - bi)

    print(ans)


if __name__ == "__main__":
    main()
