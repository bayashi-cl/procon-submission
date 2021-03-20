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
    k = len(N)
    if k == 1:
        print(0)
        return
    ans = 0
    for i in range(k // 2):
        if i == 0:
            pass
        else:
            ans += 10 ** i - 10 ** (i - 1)

    if k % 2 == 1:
        ans += 10 ** (i + 1) - 10 ** i
    else:
        left = int(N[: k // 2])
        right = int(N[k // 2 :])
        ans += left - 10 ** i + 1
        if left > right:
            ans -= 1

    print(ans)


if __name__ == "__main__":
    main()
