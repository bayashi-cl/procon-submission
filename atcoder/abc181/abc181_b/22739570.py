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
    ans = 0
    for _ in [None] * n:
        a, b = map(int, sinput().split())
        ans += (a + b) * (b - a + 1) // 2

    print(ans)


if __name__ == "__main__":
    main()
