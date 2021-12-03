# region template
import sys
import typing
from functools import lru_cache
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


@lru_cache(maxsize=None)
def dp(i: int, j: int, k: int) -> float:
    if i >= 100 or j >= 100 or k >= 100:
        return 0.0
    res = 0.0
    res += i / (i + j + k) * (dp(i + 1, j, k) + 1)
    res += j / (i + j + k) * (dp(i, j + 1, k) + 1)
    res += k / (i + j + k) * (dp(i, j, k + 1) + 1)
    return res


def main() -> None:
    a, b, c = map(int, sinput().split())
    print(dp(a, b, c))


if __name__ == "__main__":
    main()
