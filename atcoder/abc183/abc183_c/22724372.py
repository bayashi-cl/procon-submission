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

    from itertools import permutations

    n, k = map(int, sinput().split())
    t = [list(map(int, sinput().split())) for _ in range(n)]

    ans = 0
    for p in permutations(range(1, n)):

        cost = t[0][p[0]]
        for i in range(n - 2):
            cost += t[p[i]][p[i + 1]]
        cost += t[p[-1]][0]

        if cost == k:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
