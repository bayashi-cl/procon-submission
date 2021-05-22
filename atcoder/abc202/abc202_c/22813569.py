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
    from collections import Counter

    _ = int(sinput())
    a = np.array(list(map(int, sinput().split())))
    b = np.array(list(map(int, sinput().split())))
    c = np.array(list(map(int, sinput().split())))
    bcj = b[c - 1]

    cnt_a = Counter(a.tolist())
    cnt_bcj = Counter(bcj.tolist())

    co_key = cnt_a.keys() & cnt_bcj.keys()

    ans = 0
    for key in co_key:
        ans += cnt_a[key] * cnt_bcj[key]
    print(ans)


if __name__ == "__main__":
    main()
