# region template
import sys
import typing
import statistics
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n = int(sinput())
    x = []
    y = []
    for _ in range(n):
        xi, yi = map(int, sinput().split())
        x.append(xi)
        y.append(yi)

    xa = statistics.median_high(x)
    ya = statistics.median_high(y)
    ans = 0
    for xi, yi in zip(x, y):
        ans += abs(xa - xi)
        ans += abs(ya - yi)

    print(ans)


if __name__ == "__main__":
    main()
