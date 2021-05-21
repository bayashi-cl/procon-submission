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

    a = 7 % k
    for i in range(1, k + 10):
        if a == 0:
            print(i)
            break
        a = (10 * a + 7) % k

    else:
        print(-1)


if __name__ == "__main__":
    main()
