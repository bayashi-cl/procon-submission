# region template
import sys
import typing
from math import log2
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
    for k in range(70):
        if 2 ** (k + 1) > n:
            print(k)
            return


if __name__ == "__main__":
    main()
