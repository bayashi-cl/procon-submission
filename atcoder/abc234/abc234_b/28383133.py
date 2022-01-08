import functools
import sys
import typing
from math import hypot
from itertools import combinations
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    pos = [tuple(map(int, sinput().split())) for _ in range(n)]

    ans = 0.0
    for p1, p2 in combinations(pos, 2):
        ans = max(ans, hypot(p2[0] - p1[0], p2[1] - p1[1]))
    print(ans)


if __name__ == "__main__":
    main()
