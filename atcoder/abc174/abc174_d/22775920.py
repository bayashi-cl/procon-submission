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
    altar_ = sinput().strip()
    altar = [1 if a == "R" else 0 for a in altar_]
    n_red = altar.count(1)

    altar_cs = list(accumulate(altar))
    ans = altar_cs[-1]
    for i in range(1, n + 1):  # i番目から白
        left_red = altar_cs[i - 1]
        left_white = i - left_red  # remove
        right_red = n_red - left_red  # remove
        move = max(left_white, right_red)
        ans = min(ans, move)

    print(ans)


if __name__ == "__main__":
    main()
