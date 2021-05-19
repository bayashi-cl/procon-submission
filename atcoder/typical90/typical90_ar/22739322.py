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

    n, q = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    offset = 0

    for _ in [None] * q:
        t, x, y = map(int, sinput().split())
        x = (x - 1 - offset) % n
        y = (y - 1 - offset) % n
        if t == 1:
            a[x], a[y] = a[y], a[x]
        elif t == 2:
            offset += 1
        else:
            print(a[x])


if __name__ == "__main__":
    main()
