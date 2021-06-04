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
    a, b = map(int, sinput().split())
    g = gcd(a, b)
    ans = a * b // g

    print(ans)


if __name__ == "__main__":
    main()
