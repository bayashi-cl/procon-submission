N, W = map(int, input().split())
v_max = 1000 * N + 1
dp = [[float("inf")] * v_max for _ in range(N + 1)]
dp[0][0] = 0
for i in range(1, N + 1):
    w, v = map(int, input().split())
    for j in range(v_max):
        dp[i][j] = dp[i - 1][j]
        if j - v >= 0:
            dp[i][j] = min(dp[i - 1][j - v] + w, dp[i - 1][j])

ans = 0
for i in range(v_max):
    if dp[N][i] <= W:
        ans = max(ans, i)
print(ans)
