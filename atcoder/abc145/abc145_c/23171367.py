# region template
import sys
import typing
from itertools import permutations
import math
from statistics import mean

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
    pos = [tuple(map(int, sinput().split())) for _ in range(n)]
    dist = [[0.0] * n for _ in range(n)]
    for i in range(n - 1):
        for j in range(i + 1, n):
            d = math.dist(pos[i], pos[j])
            dist[i][j] = d
            dist[j][i] = d
    d_list = []
    for per in permutations(range(n)):
        d = 0.0
        for i in range(n - 1):
            d += dist[per[i]][per[i + 1]]
        d_list.append(d)

    print(mean(d_list))


if __name__ == "__main__":
    main()
