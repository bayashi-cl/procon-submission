# region template
from __future__ import annotations

import sys
from typing import Callable, Final

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


class Combinations:
    def __init__(self, n_max: int, mod: int = 1000000007) -> None:
        self.n_max = n_max + 1
        self.mod = mod

        self.fact = [0] * self.n_max
        self.factinv = [0] * self.n_max

        self.fact[0] = 1
        for i in range(1, self.n_max):
            self.fact[i] = (i * self.fact[i - 1]) % self.mod
        for i in range(self.n_max):
            self.factinv[i] = self._div(1, self.fact[i], self.mod)

    def _div(self, a: int, b: int, m: int) -> int:
        return a * pow(b, m - 2, m) % m

    def ncr(self, n: int, r: int) -> int:
        if n > self.n_max - 1:
            raise ValueError
        if n < r or r < 0:
            return 0
        return (
            (self.fact[n] * self.factinv[r] % self.mod) * self.factinv[n - r] % self.mod
        )


def main() -> None:
    n = int(sinput())
    comb = Combinations(n, MOD)
    for k in range(1, n + 1):
        ans = 0
        for i in range(1, n // k + 2):
            s = n - (k - 1) * (i - 1)
            ans += comb.ncr(s, i)
            ans %= MOD
        print(ans)


if __name__ == "__main__":
    main()
