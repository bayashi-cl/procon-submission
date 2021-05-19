def main() -> None:
    # region template
    import sys
    import typing

    sys.setrecursionlimit(10 ** 6)
    Vec = typing.List[int]  # noqa:F841
    VecVec = typing.List[Vec]  # noqa:F841
    sinput: typing.Callable[..., str] = sys.stdin.readline  # noqa:F841
    MOD: int = 1000000007  # noqa:F841
    INF: float = float("Inf")  # noqa:F841
    IINF: int = 4611686018427387903  # noqa:F841
    # endregion

    k = int(sinput())

    if k % 9 != 0:
        print(0)
        return

    dp = [0] * (k + 1)
    dp[0] = 1

    for i in range(1, k + 1):
        for j in range(1, 10):
            if i - j < 0:
                continue
            dp[i] += dp[i - j]
            dp[i] %= MOD

    print(dp[k])


if __name__ == "__main__":
    main()
