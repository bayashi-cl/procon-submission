# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from math import isclose, sqrt

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, c = map(int, sinput().split())
    if c >= a + b:
        if 4 * a * b < (c - (a + b)) ** 2:
            print("Yes")
        else:
            print("No")
    else:
        print("No")


if __name__ == "__main__":
    main()
