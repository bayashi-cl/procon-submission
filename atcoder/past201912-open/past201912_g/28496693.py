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


def bit(x: int, n: int, k: int) -> List[List[int]]:
    res: List[List[int]] = [list() for _ in range(k)]
    for i in range(n):
        res[x % k].append(i)
        x //= k
    return res


def main() -> None:
    n = int(sinput())
    a = [[0] * n for _ in range(n)]
    for i in range(n - 1):
        a[i][i + 1 :] = list(map(int, sinput().split()))

    def cost(l: List[int]) -> int:
        k = len(l)
        res = 0
        for i in range(k):
            for j in range(i + 1, k):
                res += a[l[i]][l[j]]
        return res

    ans = -IINF
    for g in [1, 2, 3]:
        for s in range(g ** n):
            c = 0
            for l in bit(s, n, g):
                c += cost(l)
            ans = max(ans, c)

    print(ans)


if __name__ == "__main__":
    main()
