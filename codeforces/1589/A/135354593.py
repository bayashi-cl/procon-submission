# region template
import sys
import typing
from math import isclose
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def check(u, v, x, y):
    print(isclose(x / u + y / v, (x + y) / (u + v)), file=sys.stderr)


def main() -> None:
    t = int(sinput())
    for _ in range(t):
        u, v = map(int, sinput().split())
        # check(u, v, u ** 2, -(v ** 2))
        print(u ** 2, -(v ** 2))


if __name__ == "__main__":
    main()
