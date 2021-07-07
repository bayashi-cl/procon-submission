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
    a, b, c = map(int, sinput().split())

    for i in range(1, b):
        if (a * i) % b == c:
            print("YES")
            break
    else:
        print("NO")


if __name__ == "__main__":
    main()
