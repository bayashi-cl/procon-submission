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
    n, k = map(int, sinput().split())
    ans = 0
    for b in range(1, n + 1):
        if b <= k:
            continue
        d, m = divmod(n + 1, b)
        ans += (b - k) * d + max(m - k, 0)
    if k == 0:
        ans -= n
    print(ans)


if __name__ == "__main__":
    main()
