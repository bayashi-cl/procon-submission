# region template
import sys
import typing
from itertools import combinations
from math import gcd
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
    pos: List[Tuple[int, int]] = []
    for _ in range(n):
        x, y = map(int, sinput().split())
        pos.append((x, y))

    pos.sort()
    magic: Set[Tuple[int, int]] = set()
    for pi, pj in combinations(pos, 2):
        dx = pj[0] - pi[0]
        dy = pj[1] - pi[1]
        g = gcd(dx, dy)
        magic.add((dx // g, dy // g))

    print(len(magic) * 2)


if __name__ == "__main__":
    main()
