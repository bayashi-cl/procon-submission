# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import defaultdict

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def prime_factorize(n: int) -> Dict[int, int]:
    res: typing.DefaultDict[int, int] = defaultdict(int)
    while n % 2 == 0:
        res[2] += 1
        n //= 2
    f = 3
    while f * f <= n:
        if n % f == 0:
            res[f] += 1
            n //= f
        else:
            f += 2
    if n != 1:
        res[n] += 1
    return res


def main() -> None:
    n, p = map(int, sinput().split())
    prime = prime_factorize(p)

    ans = 1
    for k, v in prime.items():
        ans *= k ** (v // n)
    print(ans)


if __name__ == "__main__":
    main()
