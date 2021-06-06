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
    s = sinput().strip()
    dp = [[0] * 13 for _ in range(len(s))]
    if s[-1] == "?":
        for j in range(10):
            dp[0][j] = 1
    else:
        dp[0][int(s[-1])] = 1

    for i in range(1, len(s)):
        d = s[-i - 1]
        if d == "?":
            pow10i = pow(10, i, 13)

            for j in range(13):
                for k in range(10):
                    offset = k * pow10i % 13
                    dp[i][j] += dp[i - 1][(j - offset) % 13]
                dp[i][j] %= MOD

        else:
            offset = (int(d) * pow(10, i, 13)) % 13
            for j in range(13):
                dp[i][j] = dp[i - 1][(j - offset) % 13]
                dp[i][j] %= MOD

    print(dp[-1][5])


if __name__ == "__main__":
    main()
