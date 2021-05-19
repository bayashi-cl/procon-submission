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

    from itertools import combinations

    n = int(sinput())
    point = [tuple(map(int, sinput().split())) for _ in range(n)]

    ans = False
    for comb in combinations(range(n), 3):
        xa, ya = point[comb[0]]
        xb, yb = point[comb[1]]
        xc, yc = point[comb[2]]

        if (xc - xb) * (yb - ya) == (xb - xa) * (yc - yb):
            ans = True
            break

    if ans:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
