# region template
import sys
import typing
from math import comb

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
    r = n - k
    for i in range(1, k + 1):
        place = comb(r + 1, i) % MOD
        perm = comb(k - 1, i - 1) % MOD
        print(place * perm % MOD)


if __name__ == "__main__":
    main()
