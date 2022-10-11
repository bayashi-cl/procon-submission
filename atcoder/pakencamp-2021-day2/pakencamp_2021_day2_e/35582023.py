from typing import Final

MOD: Final[int] = 998244353

n, m = map(int, input().split())
print(m * (m - 1) * pow(m - 2, n - 2, MOD) % MOD)
