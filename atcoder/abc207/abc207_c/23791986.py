# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from itertools import combinations
from decimal import Decimal

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
    seg = []
    for _ in range(n):
        t, l, r = map(int, sinput().split())
        # [l, r)
        if t == 1:
            seg.append((l, r))
        elif t == 2:
            seg.append((l, r - 0.2))
        elif t == 3:
            seg.append((l + 0.2, r))
        elif t == 4:
            seg.append((l + 0.2, r - 0.2))
    ans = 0
    for i, j in combinations(range(n), 2):
        if (seg[j][0] <= seg[i][0] and seg[i][0] <= seg[j][1]) or (
            seg[j][0] <= seg[i][1] and seg[i][1] <= seg[j][1]
        ):
            ans += 1
        elif (seg[i][0] <= seg[j][0] and seg[j][0] <= seg[i][1]) or (
            seg[i][0] <= seg[j][1] and seg[j][1] <= seg[i][1]
        ):
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
