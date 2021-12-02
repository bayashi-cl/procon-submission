# region template
import sys
import typing
from itertools import accumulate
from operator import itemgetter
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
    n, w = map(int, sinput().split())
    req = [tuple(map(int, sinput().split())) for _ in range(n)]
    end = max(req, key=itemgetter(1))[1]
    time = [0] * (end + 1)
    for s, t, p in req:
        time[s] += p
        time[t] -= p

    time = list(accumulate(time))
    if max(time) <= w:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
