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
    from bisect import bisect_right as bisect

    n, m, k = map(int, sinput().split())

    # |A| <= |B|
    if n <= m:
        a = list(map(int, sinput().split()))
        b = list(map(int, sinput().split()))
    else:
        b = list(map(int, sinput().split()))
        a = list(map(int, sinput().split()))

    a_cs = [0] + list(accumulate(a))
    b_cs = list(accumulate(b))

    ans = 0
    for i in range(len(a_cs)):
        left_time = k - a_cs[i]
        if left_time < 0:
            continue
        readable = bisect(b_cs, left_time)
        ans = max(ans, i + readable)
    print(ans)


if __name__ == "__main__":
    main()
