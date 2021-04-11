# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
import math

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    r, x, y = map(int, sinput().split())
    dist = math.sqrt(x ** 2 + y ** 2)
    if dist == r:
        print(1)
    elif dist < r:
        print(2)
    else:
        print(math.ceil(dist / r))


if __name__ == "__main__":
    main()
