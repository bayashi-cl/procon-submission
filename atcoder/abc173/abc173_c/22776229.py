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

    def bit2set(n: int) -> typing.Set[int]:
        res = set()
        for i in range(n.bit_length()):
            if not (1 << i & n) == 0:
                res.add(i)
        return res

    h, w, k = map(int, sinput().split())

    board = [sinput().strip() for _ in range(h)]
    ans = 0
    for si in range(1 << h):
        bit_i = bit2set(si)
        for sj in range(1 << w):
            bit_j = bit2set(sj)
            black = 0
            for i in range(h):
                for j in range(w):
                    if i in bit_i or j in bit_j:
                        continue
                    if board[i][j] == "#":
                        black += 1
            if black == k:
                ans += 1

    print(ans)


if __name__ == "__main__":
    main()
