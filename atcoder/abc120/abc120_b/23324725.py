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


def div(n) -> list:
    i = 1
    lo = []
    hi = []
    while i * i <= n:
        if n % i == 0:
            lo.append(i)
            if n // i != i:
                hi.append(n // i)
        i += 1

    return lo + hi[::-1]


def main() -> None:
    a, b, k = map(int, sinput().split())
    g = gcd(a, b)
    ans = div(g)[-k]
    print(ans)


if __name__ == "__main__":
    main()
