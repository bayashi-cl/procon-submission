N = int(input())
h = list(map(int, input().split()))
dp = [None] * N
dp[0] = 0
dp[1] = abs(h[0] - h[1])
for i in range(1, N - 1):
    dp[i + 1] = min(dp[i] + abs(h[i] - h[i + 1]), dp[i - 1] + abs(h[i - 1] - h[i + 1]))
print(dp[-1])
