# region template
import sys
import typing
from itertools import combinations
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
    p = [tuple(map(int, sinput().split())) for _ in range(n)]

    ans = 0
    for a, b, c in combinations(p, 3):
        px = a[0] - c[0]
        py = a[1] - c[1]

        qx = b[0] - c[0]
        qy = b[1] - c[1]

        if px * qy - py * qx != 0:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
