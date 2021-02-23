N = int(input())
u = [list(map(int, input().split())) for _ in range(N)]

dp = [[0, 0, 0] for _ in range(N)]
dp[0] = u[0]

for i in range(N - 1):
    for j in range(3):
        for k in range(3):
            if j == k:
                continue
            temp = dp[i][j] + u[i + 1][k]
            if temp > dp[i + 1][k]:
                dp[i + 1][k] = temp
print(max(dp[-1]))
