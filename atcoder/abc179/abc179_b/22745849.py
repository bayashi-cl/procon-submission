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

    combo = 0

    for _ in [None] * n:
        d1, d2 = map(int, sinput().split())
        if d1 == d2:
            combo += 1
            if combo == 3:
                print("Yes")
                break
        else:
            combo = 0
    else:
        print("No")


if __name__ == "__main__":
    main()
