from math import factorial

n = int(input())
mod = 998244353
a = factorial(2 * n) % mod
b = pow(2, n, mod)
c = pow(factorial(n + 1) % mod, -1, mod)
print(a * b * c % mod)
