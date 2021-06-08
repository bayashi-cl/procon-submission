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
    n, m = map(int, sinput().split())
    a = set(map(int, sys.stdin.read().split()))

    dp = [0] * (n + 1)
    dp[0] = 1
    for i in range(n):
        if not i + 1 in a and i + 1 <= n:
            dp[i + 1] += dp[i]
            dp[i + 1] %= MOD
        if not i + 2 in a and i + 2 <= n:
            dp[i + 2] += dp[i]
            dp[i + 2] %= MOD
    print(dp[n] % MOD)


if __name__ == "__main__":
    main()
