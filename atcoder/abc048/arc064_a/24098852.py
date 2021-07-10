# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, x = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    ans = 0
    for i in range(n - 1):
        if a[i] > x:
            ans += a[i] - x
            a[i] = x

        if a[i] + a[i + 1] > x:
            ans += a[i + 1] - (x - a[i])
            a[i + 1] = x - a[i]

    print(ans)


if __name__ == "__main__":
    main()
