n, t = map(int, input().split())
a = list(map(int, input().split()))

ans = a[0]
for i in range(n - 1):
    if a[i] <= a[i + 1]:
        ans += a[i + 1] - a[i]
    else:
        ans += t - (a[i] - a[i + 1])
print(ans)
