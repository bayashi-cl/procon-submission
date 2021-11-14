# region template
import sys
import typing
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
    ans = 0
    for a in range(1, n + 1):
        if a ** 3 > n:
            break
        for b in range(a, n + 1):
            if a * b ** 2 > n:
                break
            max_c = n // (a * b)
            ans += max_c - b + 1
    print(ans)


if __name__ == "__main__":
    main()
