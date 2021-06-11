# region template
import sys
import typing
from collections import Counter
from itertools import chain, combinations

# from math import comb

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def prime_factorize(n: int) -> typing.List[int]:
    res = []
    while n % 2 == 0:
        res.append(2)
        n //= 2
    f = 3
    while f * f <= n:
        if n % f == 0:
            res.append(f)
            n //= f
        else:
            f += 2
    if n != 1:
        res.append(n)
    return res


def main() -> None:
    n = int(sinput())
    factor = []

    for i in range(2, n + 1):
        factor.append(prime_factorize(i))

    cnt = Counter(chain.from_iterable(factor))
    n_factor = list(cnt.values())
    n_factor.sort()
    ans = 0

    c_2 = 0
    c_4 = 0
    c_14 = 0
    c_24 = 0
    c_74 = 0

    for f in n_factor:
        if f >= 2:
            c_2 += 1
        if f >= 4:
            c_4 += 1
        if f >= 14:
            c_14 += 1
        if f >= 24:
            c_24 += 1
        if f >= 74:
            c_74 += 1

    c1 = c_74
    c2 = c_24 * (c_2 - 1)
    c3 = c_14 * (c_4 - 1)
    c4 = c_4 * (c_4 - 1) * (c_2 - 2) // 2
    ans = c1 + c2 + c3 + c4
    print(ans)


if __name__ == "__main__":
    main()
