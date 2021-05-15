# region template
import sys
from typing import Callable


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: int = sys.maxsize
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    H, W = map(int, sinput().split())
    a_ = [sinput().strip() for _ in range(H)]
    a = [[0] * W for _ in range(H)]
    for i in range(H):
        for j in range(W):
            if a_[i][j] == "+":
                a[i][j] = 1
            else:
                a[i][j] = -1

    dp = [[0] * W for _ in range(H)]  # t-a

    for i in range(H - 1, -1, -1):
        for j in range(W - 1, -1, -1):
            if i == H - 1 and j == W - 1:
                dp[i][j] = 0
                continue
            if (i + j) % 2 == 0:
                dp[i][j] = -INF
                if i < H - 1:
                    dp[i][j] = max(dp[i][j], dp[i + 1][j] + a[i + 1][j])
                if j < W - 1:
                    dp[i][j] = max(dp[i][j], dp[i][j + 1] + a[i][j + 1])
            else:
                dp[i][j] = INF
                if i < H - 1:
                    dp[i][j] = min(dp[i][j], dp[i + 1][j] - a[i + 1][j])
                if j < W - 1:
                    dp[i][j] = min(dp[i][j], dp[i][j + 1] - a[i][j + 1])

    ans = dp[0][0]
    if ans > 0:
        print("Takahashi")
    elif ans < 0:
        print("Aoki")
    else:
        print("Draw")


if __name__ == "__main__":
    main()
