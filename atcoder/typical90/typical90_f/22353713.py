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
    n, k = map(int, sinput().split())
    s = sinput().strip()

    table = [[INF] * (n + 1) for _ in range(26)]
    for i in range(n - 1, -1, -1):
        for l in range(26):
            table[l][i] = table[l][i + 1]
        table[ord(s[i]) - 97][i] = i

    ans = ""
    pos = 0
    for i in range(k):
        for j in range(26):
            tmp = table[j][pos]
            if n - tmp >= k - i:
                ans += chr(97 + j)
                pos = table[j][tmp] + 1
                break

    print(ans)


if __name__ == "__main__":
    main()
