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


def main() -> None:
    mod = 1000000007
    s = int(sinput())
    if s < 3:
        print(0)
        return

    @lru_cache(maxsize=None)
    def rec(x: int) -> int:
        if x < 3:
            return 0
        res = 1
        for i in range(3, x):
            res += rec(x - i)
            res %= mod
        return res

    print(rec(s))


if __name__ == "__main__":
    main()
