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
    sl = [{1, 3, 5, 7, 8, 10, 12}, {4, 6, 9, 11}, {2}]
    x, y = map(int, sinput().split())
    for s in sl:
        if x in s and y in s:
            print("Yes")
            break
    else:
        print("No")


if __name__ == "__main__":
    main()
