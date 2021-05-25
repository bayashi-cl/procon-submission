# region template
import sys
import typing
from itertools import combinations_with_replacement

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m, q = map(int, sinput().split())
    data = [tuple(map(int, sinput().split())) for _ in range(q)]

    ans = 0
    for comb in combinations_with_replacement(range(1, m + 1), n):
        point = 0
        for d in data:
            if comb[d[1] - 1] - comb[d[0] - 1] == d[2]:
                point += d[3]

        ans = max(ans, point)

    print(ans)


if __name__ == "__main__":
    main()
