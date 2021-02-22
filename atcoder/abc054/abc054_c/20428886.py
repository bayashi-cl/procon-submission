N, M = map(int, input().split())
adj = [list() for _ in range(N)]
for i in range(M):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    adj[a].append(b)
    adj[b].append(a)
dp = [[0] * N for _ in range(1 << N)]
dp[1][0] = 1
for s in range(1 << N):
    for v in range(N):
        if s & (1 << v) == 0:
            continue
        sub = s ^ (1 << v)
        for u in adj[v]:
            if (sub & (1 << u)) and (u in adj[v]):
                dp[s][v] += dp[sub][u]
ans = sum(dp[-1])
print(ans)
