from __future__ import annotations

n = int(input())
p = map(int, input().split())

graph: list[list[int]] = [[] for _ in range(n)]
for i, pi in enumerate(p, 1):
    graph[pi].append(i)


ans = [0] * n


def dfs(now: int) -> int:
    res = 1
    for c in graph[now]:
        res += dfs(c)
    ans[now] = res
    return res


dfs(0)
print(*ans, sep="\n")
