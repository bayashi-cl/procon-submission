N, W = map(int, input().split())
value = list()
weight = list()
for i in range(N):
    v, w = map(int, input().split())
    value.append(v)
    weight.append(w)

dp = [[None] * (W + 1) for _ in range(N + 1)]
for i in range(W + 1):
    dp[0][i] = 0
for i in range(N):
    for w in range(W + 1):
        if w >= weight[i]:
            dp[i + 1][w] = max(dp[i][w - weight[i]] + value[i], dp[i][w])
        else:
            dp[i + 1][w] = dp[i][w]

print(dp[-1][-1])

