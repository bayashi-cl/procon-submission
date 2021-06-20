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
    n, m = map(int, sinput().split())
    if n == 1 or m == 1:
        if n == 1 and m == 1:
            print(1)
        else:
            print(max(n, m) - 2)
    else:
        print((n - 2) * (m - 2))


if __name__ == "__main__":
    main()
