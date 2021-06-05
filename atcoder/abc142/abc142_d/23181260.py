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


def prime_factorize(n):
    a = []
    while n % 2 == 0:
        a.append(2)
        n //= 2
    f = 3
    while f * f <= n:
        if n % f == 0:
            a.append(f)
            n //= f
        else:
            f += 2
    if n != 1:
        a.append(n)
    return a


def main() -> None:
    a, b = map(int, sinput().split())
    g = gcd(a, b)
    p = prime_factorize(g)
    ans = len(set(p)) + 1
    print(ans)


if __name__ == "__main__":
    main()
