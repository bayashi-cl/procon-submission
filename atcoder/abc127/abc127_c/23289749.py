# region template
import sys
import typing
from itertools import accumulate

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    imos = [0] * (n + 10)
    for i in range(m):
        l, r = map(int, sinput().split())
        imos[l] += 1
        imos[r + 1] -= 1
    imos = list(accumulate(imos))
    print(imos.count(m))


if __name__ == "__main__":
    main()
