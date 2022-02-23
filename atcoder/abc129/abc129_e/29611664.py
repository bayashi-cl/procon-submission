import sys


MOD7 = 1000000007


def main() -> None:
    l = input()
    n = len(l)
    dp = [[0] * (n + 1) for _ in range(2)]
    dp[0][0] = 1
    for i, li in enumerate(l):
        if li == "0":
            dp[0][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * 3
        else:
            dp[0][i + 1] += dp[0][i] * 2
            dp[1][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * 3

        dp[0][i + 1] %= MOD7
        dp[1][i + 1] %= MOD7

    print((dp[0][n] + dp[1][n]) % MOD7)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
