# region template
import sys
import typing
from itertools import permutations

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, c = map(int, sinput().split())
    d = [tuple(map(int, sinput().split())) for _ in range(c)]
    color = [tuple(map(lambda x: int(x) - 1, sinput().split())) for _ in range(n)]

    zero = [0] * c
    one = [0] * c
    two = [0] * c

    for i in range(n):
        for j in range(n):
            if (i + j) % 3 == 0:
                zero[color[i][j]] += 1
            elif (i + j) % 3 == 1:
                one[color[i][j]] += 1
            elif (i + j) % 3 == 2:
                two[color[i][j]] += 1

    zero_cost = [0] * c
    one_cost = [0] * c
    two_cost = [0] * c

    for arr in range(c):
        for dep in range(c):
            zero_cost[arr] += zero[dep] * d[dep][arr]
            one_cost[arr] += one[dep] * d[dep][arr]
            two_cost[arr] += two[dep] * d[dep][arr]

    ans = INF
    for p, q, r in permutations(range(c), 3):
        ans = min(ans, zero_cost[p] + one_cost[q] + two_cost[r])
    print(ans)


if __name__ == "__main__":
    main()
