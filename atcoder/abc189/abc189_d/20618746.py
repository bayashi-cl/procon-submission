N = int(input())
s = [""] * N
for i in range(N):
    s[i] = input()
dp = [-1] * (N + 1)
dp[0] = 1
for i in range(N):
    if s[i] == "OR":
        dp[i + 1] = dp[i] + 2 ** (i + 1)
    else:
        dp[i + 1] = dp[i]
print(dp[-1])
