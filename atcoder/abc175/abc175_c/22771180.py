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

    x, k, d = map(int, sinput().split())

    if (ans := abs(x) - (k * d)) < 0:
        arr, pos = divmod(abs(x), d)
        if (k - arr) % 2 == 0:
            ans = pos
        else:
            ans = abs(pos - d)

    print(ans)


if __name__ == "__main__":
    main()
