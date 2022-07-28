n, x, y, z = map(int, input().split())
ans = 0
for _ in range(n):
    ai, bi = map(int, input().split())
    if ai >= x and bi >= y and ai + bi >= z:
        ans += 1
print(ans)
