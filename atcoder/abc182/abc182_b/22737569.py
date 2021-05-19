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

    import numpy as np

    _ = sinput()
    a = np.array(list(map(int, sinput().split())), dtype=np.int64)

    ans = 0
    max_almost = -1
    for k in range(2, np.max(a) + 1):
        almost = np.count_nonzero(a % k == 0)
        if almost >= max_almost:
            max_almost = almost
            ans = k

    print(ans)


if __name__ == "__main__":
    main()
