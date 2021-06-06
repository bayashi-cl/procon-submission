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
    t = list(map(int, sinput().split()))
    t.sort()
    t_sum = sum(t)
    dp = [[False] * (t_sum + 1) for _ in range(n)]
    dp[0][0] = True
    dp[0][t[0]] = True
    for i in range(1, n):
        for j in range(t_sum + 1):
            dp[i][j] = dp[i - 1][j]
            if j - t[i] >= 0:
                dp[i][j] = dp[i][j] or dp[i - 1][j - t[i]]

    harf = -(-sum(t) // 2)
    for i, tf in enumerate(dp[-1][harf:]):
        if tf:
            print(i + harf)
            break


if __name__ == "__main__":
    main()
