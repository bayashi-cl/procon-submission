# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    able = [1, 2, 3, 5, 8, 13, 21, 34]
    h, w, k = map(int, sinput().split())
    dp = [[0] * w for _ in range(h + 1)]
    dp[0][0] = 1
    for i in range(1, h + 1):
        for j in range(w):
            if j != 0:
                dp[i][j] += (
                    dp[i - 1][j - 1] * able[max(j - 2, 0)] * able[max(w - j - 2, 0)]
                )
            dp[i][j] += dp[i - 1][j] * able[max(j - 1, 0)] * able[max(w - j - 2, 0)]
            if j != w - 1:
                dp[i][j] += (
                    dp[i - 1][j + 1] * able[max(j - 1, 0)] * able[max(w - j - 3, 0)]
                )

            dp[i][j] %= MOD

    print(dp[h][k - 1])


if __name__ == "__main__":
    main()
