n, m, k = map(int, input().split())
MOD = 998244353
ans = 0
if min(n, m) == 1:
    ans = pow(k, max(n, m), MOD)
else:
    for i in range(1, k + 1):
        ans += (pow(i, n, MOD) - pow(i - 1, n, MOD)) * (pow(k - i + 1, m, MOD)) % MOD
        ans %= MOD
print(ans)
