# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from itertools import accumulate
from operator import add

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
    f = [sinput().split() for _ in range(n)]
    sale = [int("".join(fi), 2) for fi in f]

    p = [tuple(map(int, sinput().split())) for _ in range(n)]
    # cs = [tuple(accumulate(pi, add, initial=0)) for pi in p]

    ans = -INF
    for j in range(1, 1 << 10):
        pi = 0
        for i, s in enumerate(sale):
            pop = bin(s & j).count("1")
            pi += p[i][pop]
        ans = max(ans, pi)

    print(ans)


if __name__ == "__main__":
    main()
