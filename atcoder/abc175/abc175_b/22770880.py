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
    l = list(map(int, sinput().split()))

    ans = 0
    for comb in combinations(range(n), 3):
        a = l[comb[0]]
        b = l[comb[1]]
        c = l[comb[2]]
        if a == b or b == c or a == c:
            continue

        if a + b > c and a + c > b and b + c > a:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
