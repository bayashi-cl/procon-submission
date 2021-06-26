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
    s = list(sinput().strip())
    t = list(sinput().strip())

    s.sort()
    t.sort(reverse=True)
    if s < t:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
