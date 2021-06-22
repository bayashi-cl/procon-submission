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
    c = [tuple(map(int, sinput().split())) for _ in range(3)]
    diff = []
    for ci in c:
        diff.append((ci[1] - ci[0], ci[2] - ci[0]))
    if diff[0] != diff[1] or diff[2] != diff[1]:
        print("No")
        return

    diff = []
    for ci in zip(*c):
        diff.append((ci[1] - ci[0], ci[2] - ci[0]))
    if diff[0] != diff[1] or diff[2] != diff[1]:
        print("No")
        return

    print("Yes")


if __name__ == "__main__":
    main()
