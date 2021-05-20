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

    from math import ceil

    x, y, a, b = map(int, sinput().split())
    e = 0

    while x * a < x + b:
        x *= a
        if x >= y:
            print(e)
            return
        e += 1

    d, m = divmod(y - x, b)
    ans = e + d - 1
    if m:
        ans += 1
    print(ans)


if __name__ == "__main__":
    main()
