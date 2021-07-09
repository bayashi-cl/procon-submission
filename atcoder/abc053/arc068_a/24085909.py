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
    x = int(sinput())
    d, m = divmod(x, 11)
    d *= 2
    if m > 0:
        d += 1
    if m > 6:
        d += 1
    print(d)


if __name__ == "__main__":
    main()
