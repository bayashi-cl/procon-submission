# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final

from math import floor, ceil

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    x, y, z = map(int, sinput().split())
    print(ceil(y / x * z) - 1)


if __name__ == "__main__":
    main()
