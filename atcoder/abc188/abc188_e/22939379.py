# region template
import sys
import typing
from collections import deque


sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    graph: VecVec = [[] for _ in range(n)]
    for _ in range(m):
        x, y = map(int, sinput().split())
        graph[x - 1].append(y - 1)

    dp = [-INF] * n
    ans = -INF
    for i in reversed(range(n)):
        for adj in graph[i]:
            dp[i] = max(dp[i], dp[adj])
        if dp[i] != -INF:
            ans = max(ans, dp[i] - a[i])
        dp[i] = max(dp[i], a[i])
    print(ans)


if __name__ == "__main__":
    main()
