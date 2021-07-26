# region template
import sys
import typing
from operator import itemgetter
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
    a = [list(map(int, sinput().split())) for _ in range(n)]
    edge = []

    for i in range(n):
        for j in range(n):
            if i < j:
                edge.append((a[i][j], i, j))

            for k in range(n):
                if a[i][j] > a[i][k] + a[k][j]:
                    print(-1)
                    return

    edge.sort(reverse=True)
    ans = sum(c[0] for c in edge)
    for c, f, t in edge:
        for k in range(n):
            if k == f or k == t:
                continue
            if a[f][t] == a[f][k] + a[k][t]:
                a[f][t] = INF
                a[t][f] = INF
        if a[f][t] == INF:
            ans -= c
    print(ans)


if __name__ == "__main__":
    main()
