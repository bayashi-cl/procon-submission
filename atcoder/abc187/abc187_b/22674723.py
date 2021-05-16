# region template
import sys
import typing
from itertools import combinations

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    point = [tuple(map(int, sinput().split())) for _ in range(n)]

    ans = 0
    for c in combinations(range(n), 2):
        i = point[c[0]]
        j = point[c[1]]
        a = (j[1] - i[1]) / (j[0] - i[0])
        if a >= -1 and a <= 1:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
