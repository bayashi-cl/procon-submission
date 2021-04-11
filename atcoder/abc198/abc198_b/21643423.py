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
    N = sinput().strip()
    for i in range(11):
        if len(N) % 2 == 0:
            mid = len(N) // 2
            if N[:mid] == (N[mid:])[::-1]:
                print("Yes")
                break
        else:
            mid = len(N) // 2 + 1
            if N[:mid] == (N[mid - 1 :])[::-1]:
                print("Yes")
                break

        N = "0" + N
    else:
        print("No")


if __name__ == "__main__":
    main()
