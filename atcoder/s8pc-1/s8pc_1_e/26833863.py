# region template
import sys
import typing
from itertools import accumulate
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n, q = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    c = [0] + list(map(lambda x: int(x) - 1, sinput().split())) + [0]

    dist = [0] * n
    for i in range(1, n):
        dist[i] = pow(a[i - 1], a[i], MOD)

    dist = list(accumulate(dist))
    ans = 0
    for i in range(q + 1):
        ans += abs(dist[c[i + 1]] - dist[c[i]])
        ans %= MOD

    print(ans)


if __name__ == "__main__":
    main()
