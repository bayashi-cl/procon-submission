n, a, b = map(int, input().split())
ans = 0
for i in range(1, n + 1):
    s = 0
    for k in str(i):
        s += int(k)

    if (s >= a) and (s <= b):
        ans += i
print(ans)
