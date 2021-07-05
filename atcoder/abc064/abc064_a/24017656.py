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
    r, g, b = map(int, sinput().split())
    if (100 * r + 10 * g + b) % 4 == 0:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
