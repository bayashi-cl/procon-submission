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
    n = int(sinput())
    lrc = [tuple(map(int, sinput().split())) for _ in range(n)]

    width = []
    cost = []

    max_w = 0
    min_c = IINF
    for l, r, c in lrc:
        if r - l + 1 > max_w:
            max_w = r - l + 1
            min_c = c
        elif r - l + 1 == max_w:
            min_c = min(min_c, c)
        width.append(max_w)
        cost.append(min_c)

    left = IINF
    left_cost = 0
    right = -IINF
    right_cost = 0

    for i, (l, r, c) in enumerate(lrc):
        if l < left:
            left = l
            left_cost = c
        elif l == left:
            left_cost = min(left_cost, c)

        if r > right:
            right = r
            right_cost = c
        elif r == right:
            right_cost = min(right_cost, c)

        if right - left + 1 > width[i]:
            cost[i] = left_cost + right_cost
        elif right - left + 1 == width[i]:
            cost[i] = min(cost[i], left_cost + right_cost)

    print(*cost, sep="\n")


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
