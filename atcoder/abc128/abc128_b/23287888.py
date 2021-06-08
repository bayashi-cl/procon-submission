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
    n = int(sinput())

    shop = []
    for i in range(1, n + 1):
        a, b = sinput().split()
        shop.append((i, a, int(b)))

    shop.sort(key=itemgetter(2), reverse=True)
    shop.sort(key=itemgetter(1))

    for c, _, _ in shop:
        print(c)


if __name__ == "__main__":
    main()
