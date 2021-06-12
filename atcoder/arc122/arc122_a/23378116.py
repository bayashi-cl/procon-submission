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
    n = int(sinput())
    a = list(map(int, sinput().split()))

    if n == 1:
        print(a[0])
        return

    dp = [[0] * 2 for _ in range(n + 1)]
    dp[1] = [1, 1]
    for i in range(2, n + 1):
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % MOD
        dp[i][1] = dp[i - 1][0]

    ans = a[0] * sum(dp[n - 1])
    for i in range(1, n):
        # plus
        l = sum(dp[i - 1])
        if i - 1 <= 0:
            l = 1
        r = sum(dp[n - i - 1])
        if i == n - 1:
            r = 1
        ans += a[i] * l * r

        # minus
        l = sum(dp[i - 2])
        if i - 2 <= 0:
            l = 1

        r = sum(dp[n - i - 2])
        if n - i - 2 <= 0:
            r = 1
        ans -= a[i] * l * r

        ans %= MOD

    print(ans)


if __name__ == "__main__":
    main()
