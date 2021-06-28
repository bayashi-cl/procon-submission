# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from functools import lru_cache

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    @lru_cache(None)
    def lucas(x: int) -> int:
        if x == 0:
            return 2
        elif x == 1:
            return 1
        else:
            return lucas(x - 1) + lucas(x - 2)

    n = int(sinput())
    print(lucas(n))


if __name__ == "__main__":
    main()
