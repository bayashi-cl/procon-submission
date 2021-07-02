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
    if s[3] != "-":
        print("No")
        return
    if s[:3].isdecimal() and s[4:].isdecimal():
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
