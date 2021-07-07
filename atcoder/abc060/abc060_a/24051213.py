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
    a, b, c = sinput().split()
    if a[-1] == b[0] and b[-1] == c[0]:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
