# region template
import sys
import typing
from math import log2, ceil
from fractions import Fraction

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
    ans = Fraction()

    for i in range(1, n + 1):
        case = ceil(log2(k / i))
        if case <= 0:
            de = n
        else:
            de = 2 ** case * n
        ans += Fraction(1, de)

    print(float(ans))


if __name__ == "__main__":
    main()
