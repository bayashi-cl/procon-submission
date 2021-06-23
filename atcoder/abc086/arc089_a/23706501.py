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
    n = int(sinput())
    now_x, now_y = 0, 0
    now = 0
    for _ in range(n):
        t, x, y = map(int, sinput().split())
        dist = abs(now_x - x) + abs(now_y - y)
        lim = t - now
        if dist > lim or dist % 2 != lim % 2:
            print("No")
            break
        now_x, now_y = x, y
        now = t
    else:
        print("Yes")


if __name__ == "__main__":
    main()
