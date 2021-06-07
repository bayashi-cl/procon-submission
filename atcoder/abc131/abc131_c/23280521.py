# region template
import sys
import typing
from math import gcd

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, c, d = map(int, sinput().split())
    lcm = c * d // gcd(c, d)

    def cnt(n):
        lo = -(-a // n)
        hi = b // n
        return hi - lo + 1

    div = cnt(c) + cnt(d) - cnt(lcm)
    print(b - a + 1 - div)


if __name__ == "__main__":
    main()
