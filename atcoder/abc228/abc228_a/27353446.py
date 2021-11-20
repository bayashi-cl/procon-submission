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
    s, t, x = map(int, sinput().split())
    if s < t:
        if s <= x < t:
            print("Yes")
            return
    else:
        if s <= x or x < t:
            print("Yes")
            return

    print("No")


if __name__ == "__main__":
    main()
