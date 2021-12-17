# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import defaultdict
from functools import lru_cache

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


class Osa_K:
    mx: int
    spf: List[int]  # smallest prime factor

    def __init__(self, n: int) -> None:
        self.mx = n
        self.spf = list(range(n + 1))
        self.sieve()

    def sieve(self) -> None:
        for i in range(2, self.mx + 1, 2):
            self.spf[i] = 2
        p = 3
        while p ** 2 <= self.mx:
            if self.spf[p] != p:
                p += 2
                continue
            for k in range(p ** 2, self.mx + 1, p):
                if self.spf[k] == k:
                    self.spf[k] = p
            p += 2

    def is_prime(self, n: int) -> bool:
        assert n <= self.mx
        if n <= 1:
            return False
        return self.spf[n] == n

    @lru_cache(maxsize=None)
    def factorize(self, n: int) -> Dict[int, int]:
        assert n <= self.mx
        res: typing.DefaultDict[int, int] = defaultdict(int)
        while n > 1:
            res[self.spf[n]] += 1
            n //= self.spf[n]

        return dict(res)

    def divisor(self, n: int) -> List[int]:
        res = []
        factor = list(self.factorize(n).items())
        k = len(factor)

        def dfs(depth: int, prod: int) -> None:
            if depth == k:
                res.append(prod)
                return
            p, q = factor[depth]
            for i in range(q + 1):
                dfs(depth + 1, prod)
                prod *= p

        dfs(0, 1)
        res.sort()
        return res


def main() -> None:
    n, m = map(int, sinput().split())
    a = list(set(map(int, sinput().split())))
    ban_factor = set()
    osa_k = Osa_K(10 ** 5 + 1)
    for ai in a:
        if ai == 1:
            continue
        f = set(osa_k.factorize(ai).keys())
        ban_factor |= f

    ans = [1]
    for i in range(2, m + 1):
        f = set(osa_k.factorize(i).keys())
        if ban_factor.isdisjoint(f):
            ans.append(i)
    print(len(ans))
    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
