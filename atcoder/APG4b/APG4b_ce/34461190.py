n, m = map(int, input().split())

ans = [["-"] * n for _ in range(n)]
for _ in range(m):
    w, l = map(lambda x: int(x) - 1, input().split())
    ans[w][l] = "o"
    ans[l][w] = "x"

for a in ans:
    print(*a)
