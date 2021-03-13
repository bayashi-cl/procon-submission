# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final


def plog(*obj: Any) -> None:
    print(*obj, file=sys.stderr)


sys.setrecursionlimit(10 ** 9)
sinput: Callable[[], str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    m, h = map(int, sinput().split())
    if h % m == 0:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
