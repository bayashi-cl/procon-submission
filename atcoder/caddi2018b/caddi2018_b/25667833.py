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
    n = int(sinput())
    for _ in range(n):
        a = int(sinput())
        if a % 2 == 1:
            print("first")
            return

    print("second")


if __name__ == "__main__":
    main()
