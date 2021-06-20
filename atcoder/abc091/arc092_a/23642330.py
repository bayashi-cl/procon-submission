# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from operator import itemgetter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    red = [tuple(map(int, sinput().split())) for _ in range(n)]
    blue = [tuple(map(int, sinput().split())) for _ in range(n)]
    red.sort(key=itemgetter(1), reverse=True)
    red_use = [False] * n
    ans = 0
    blue.sort()
    for bx, by in blue:
        for i in range(n):
            if red_use[i]:
                continue
            rx, ry = red[i]
            if rx < bx and ry < by:
                red_use[i] = True
                ans += 1
                break
    print(ans)


if __name__ == "__main__":
    main()
