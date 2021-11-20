# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def pm(n, p, M=MOD):
    res = 1
    while p:
        if p & 1:
            res = res * n % M
        n = n * n % M
        p >>= 1

    return res


def main() -> None:
    c, b, a = map(int, sinput().split())
    if a % MOD == 0:
        print(0)
    else:
        print(pm(a, pm(b, c, MOD - 1), MOD))


if __name__ == "__main__":
    main()
