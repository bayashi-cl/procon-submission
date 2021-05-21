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

    n, d = map(int, sinput().split())
    p = [tuple(map(int, sinput().split())) for _ in range(n)]
    ans = 0
    for point in p:
        if point[0] ** 2 + point[1] ** 2 <= d ** 2:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
