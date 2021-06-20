# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    x1, y1, x2, y2 = map(int, sinput().split())
    dx = x1 - x2
    dy = y1 - y2
    x3 = x2 + dy
    y3 = y2 - dx
    x4 = x3 + dx
    y4 = y3 + dy
    print(x3, y3, x4, y4)


if __name__ == "__main__":
    main()
