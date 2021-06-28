# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from itertools import groupby, accumulate
from operator import itemgetter

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, c = map(int, sinput().split())
    schedule = [tuple(map(int, sinput().split())) for _ in range(n)]
    record = [[0] * (10 ** 5 + 10) for _ in range(c + 1)]
    for k, g in groupby(schedule, key=itemgetter(2)):
        prog = list(g)
        for s, t, _ in prog:
            record[k][s - 1 : t] = [1] * (t - s + 1)

    ans = 0
    for time in zip(*record):
        ans = max(ans, sum(time))
    print(ans)


if __name__ == "__main__":
    main()
