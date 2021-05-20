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

    from math import hypot

    n = int(sinput())
    x_ = list(map(int, sinput().split()))
    x = [abs(xi) for xi in x_]

    print(sum(x))
    print(hypot(*x))
    print(max(x))


if __name__ == "__main__":
    main()
