# region template
import sys
import typing
from operator import itemgetter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, k = map(int, sinput().split())

    point = [0] * (2 * n)

    for i in range(n):
        a, b = map(int, sinput().split())
        point[2 * i] = b
        point[2 * i + 1] = a - b

    point.sort(reverse=True)
    print(sum(point[:k]))


if __name__ == "__main__":
    main()
