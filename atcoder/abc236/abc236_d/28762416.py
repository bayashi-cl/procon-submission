import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    b = [[0] * (2 * n) for _ in range(2 * n)]
    for i in range(2 * n - 1):
        b[i][i + 1 :] = list(map(int, sinput().split()))

    MX = 1 << (2 * n)
    ans = -1

    def dfs(s: int, c: int) -> None:
        if s == MX - 1:
            nonlocal ans
            ans = max(ans, c)

        f = -1
        for d in range(2 * n):
            if s & (1 << d):
                continue
            if f == -1:
                f = d
            else:
                dfs(s | (1 << f) | (1 << d), c ^ b[f][d])

    dfs(0, 0)
    print(ans)


if __name__ == "__main__":
    main()
