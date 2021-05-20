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

    n = int(sinput())
    u = pow(10, n, MOD)
    nine = pow(9, n, MOD) * 2
    both = pow(8, n, MOD)
    ans = (u - nine + both) % MOD
    print(ans)


if __name__ == "__main__":
    main()
