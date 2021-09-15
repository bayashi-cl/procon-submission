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
    s = sinput().strip()
    l, r = map(int, sinput().split())

    if s != "0" and s[0] == "0":
        print("No")
        return

    if l <= int(s) <= r:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
