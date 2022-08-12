n, k = map(int, input().split())
if k <= n:
    print(k**3)
elif k <= 2 * n:
    print(k**3 - 3 * (k - n) ** 3)
elif k <= 3 * n:
    print(n**3 * 6 - (3 * n - k) ** 3)
else:
    print(n**3 * 6)
