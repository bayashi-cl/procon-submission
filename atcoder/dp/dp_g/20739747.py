from functools import lru_cache
import sys

sys.setrecursionlimit(100100)

N, M = map(int, input().split())
graph = [[] for _ in range(N)]


for i in range(M):
    dep, arr = map(int, input().split())
    dep -= 1
    arr -= 1
    graph[dep].append(arr)


@lru_cache(maxsize=None)
def dp(i):
    ans = 0
    for arr in graph[i]:
        ans = max(ans, dp(arr) + 1)
    return ans


ans = 0
for j in range(N):
    ans = max(ans, dp(j))
print(ans)
