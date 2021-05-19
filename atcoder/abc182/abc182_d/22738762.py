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

    from itertools import accumulate

    n = int(sinput())
    a = list(map(int, sinput().split()))

    cs = [(a[0], a[0])]

    for i in range(1, n):
        cs.append((cs[i - 1][0] + a[i], max(cs[i - 1][1], cs[i - 1][0] + a[i])))

    pos = 0
    ans = 0
    for c in cs:
        ans = max(ans, pos + c[1])
        pos += c[0]

    print(ans)


if __name__ == "__main__":
    main()
