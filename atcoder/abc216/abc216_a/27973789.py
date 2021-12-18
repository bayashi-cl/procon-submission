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
    x, y = map(int, sinput().split("."))
    if 0 <= y <= 2:
        print(x, "-", sep="")
    elif 3 <= y <= 6:
        print(x)
    elif 7 <= y <= 9:
        print(x, "+", sep="")


if __name__ == "__main__":
    main()
