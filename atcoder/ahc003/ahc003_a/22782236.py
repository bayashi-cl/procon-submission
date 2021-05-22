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

    import random

    for i in range(1000):
        si, sj, ti, tj = map(int, sinput().split())
        res = []
        dist_i = ti - si
        dist_j = tj - sj
        if dist_i >= 0:
            res += ["D"] * abs(dist_i)
        else:
            res += ["U"] * abs(dist_i)

        if dist_j >= 0:
            res += ["R"] * abs(dist_j)
        else:
            res += ["L"] * abs(dist_j)

        random.shuffle(res)
        print("".join(res), flush=True)
        _ = sinput()


if __name__ == "__main__":
    main()
