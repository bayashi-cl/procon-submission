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
    n, k = map(int, sinput().split())
    r, s, p = map(int, sinput().split())
    t = sinput().strip()

    # r/s/p
    dp = [[0] * 3 for _ in range(n + 1)]
    for i in range(1, n + 1):
        # for j in range(3):
        if i - k > 0:
            dp[i][0] = max(dp[i - k][1], dp[i - k][2])
            dp[i][1] = max(dp[i - k][0], dp[i - k][2])
            dp[i][2] = max(dp[i - k][0], dp[i - k][1])

        if t[i - 1] == "r":
            dp[i][2] += p
        elif t[i - 1] == "s":
            dp[i][0] += r
        elif t[i - 1] == "p":
            dp[i][1] += s
        else:
            raise ValueError

    ans = sum(max(d) for d in dp[-k:])
    print(ans)


if __name__ == "__main__":
    main()
