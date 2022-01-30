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
    h, w = map(int, sinput().split())
    a = [list(map(int, sinput().split())) for _ in range(h)]
    for row in zip(*a):
        print(*row)


if __name__ == "__main__":
    main()
