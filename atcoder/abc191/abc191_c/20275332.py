h, w = map(int, input().split())
s = [list(input()) for _ in range(h)]
ans = 0

for x in range(1, h):
    for y in range(1, w):
        cnt = 0
        if s[x][y] != s[x - 1][y]:
            cnt += 1
        if s[x][y] != s[x][y - 1]:
            cnt += 2
        if s[x][y - 1] != s[x - 1][y - 1]:
            cnt += 4
        if s[x - 1][y] != s[x - 1][y - 1]:
            cnt += 8

        if cnt in [3, 6, 9, 12]:
            ans += 1

print(ans)
