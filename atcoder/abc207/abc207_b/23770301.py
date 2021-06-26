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
    a, b, c, d = map(int, sinput().split())
    k = 0
    blue = a
    red = 0
    while k <= 10 ** 7:
        if blue <= red * d:
            print(k)
            break
        blue += b
        red += c
        k += 1
    else:
        print(-1)


if __name__ == "__main__":
    main()
