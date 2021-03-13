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
    n = int(sinput())
    n_ = n
    ans = 0
    cnt = 0
    while True:
        if n_ // 1000 == 0:
            break
        cnt += 1
        n_ = n_ // 1000
    for i in range(cnt):
        ans += (1000 ** (i + 1) - 1000 ** i) * i
    ans += (n - 1000 ** cnt + 1) * cnt
    print(ans)


if __name__ == "__main__":
    main()
