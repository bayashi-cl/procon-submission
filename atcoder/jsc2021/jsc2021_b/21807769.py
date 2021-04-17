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
    n, m = map(int, sinput().split())
    a = set(map(int, sinput().split()))
    b = set(map(int, sinput().split()))

    print(*(a ^ b))


if __name__ == "__main__":
    main()
