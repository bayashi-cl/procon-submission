# region template
import sys
from typing import Callable


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    task = [list(map(int, sinput().split())) for _ in range(n)]  # deadline/cost/salary
    task.sort()
    dp = [[0] * 5001 for _ in range(n + 1)]

    for i in range(1, n + 1):
        d, c, s = task[i - 1]
        for j in range(5001):
            dp[i][j] = dp[i - 1][j]
            if j >= c and j <= d:
                dp[i][j] = max(dp[i][j], dp[i - 1][j - c] + s)

    print(max(dp[-1]))


if __name__ == "__main__":
    main()
