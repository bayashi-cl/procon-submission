# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from itertools import accumulate
from operator import add

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
    a = list(map(int, sinput().split()))
    a = list(accumulate(a, add, initial=0))

    for x in range(n - k + 1):
        print(a[x + k] - a[x])


if __name__ == "__main__":
    main()
