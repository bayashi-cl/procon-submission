# region template
import sys
import typing
from math import gcd
from functools import reduce

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def make_divisors(n):
    lower_divisors, upper_divisors = [], []
    i = 1
    while i * i <= n:
        if n % i == 0:
            lower_divisors.append(i)
            if i != n // i:
                upper_divisors.append(n // i)
        i += 1
    return lower_divisors + upper_divisors[::-1]


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))

    cand = list(set(make_divisors(a[0]) + make_divisors(a[-1])))

    cand.sort(reverse=True)
    for c in cand:
        cnt = 0
        for ai in a:
            if ai % c != 0:
                cnt += 1
        if cnt <= 1:
            print(c)
            break


if __name__ == "__main__":
    main()
