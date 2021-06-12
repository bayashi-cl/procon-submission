# region template
import sys
import typing
from collections import Counter

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


class MultiComb:
    """二項係数
    **__init__: O(n)**
    **comb: O(1)**
    """

    def __init__(self, n: int, mod: int = 10 ** 9 + 7) -> None:
        self.n = n
        self.mod = mod
        self.fact = [1, 1]
        self.factinv = [1, 1]
        self.inv = [0, 1]
        for i in range(2, self.n + 1):
            self.fact.append((self.fact[-1] * i) % self.mod)
            self.inv.append((-self.inv[self.mod % i] * (self.mod // i)) % self.mod)
            self.factinv.append((self.factinv[-1] * self.inv[-1]) % self.mod)

    def comb(self, n: int, r: int) -> int:
        if (r < 0) or (n < r):
            return 0
        r = min(r, n - r)
        return self.fact[n] * self.factinv[r] * self.factinv[n - r] % self.mod


def main() -> None:
    n, m = map(int, sinput().split())
    if m == 1:
        print(1)
        return

    cnt = list(Counter(prime_factorize(m)).values())

    mc = MultiComb(max(cnt) + n - 1)
    ans = 1
    for c in cnt:
        cmb = mc.comb(c + n - 1, c)
        ans *= cmb
        ans %= MOD
    print(ans)


if __name__ == "__main__":
    main()
