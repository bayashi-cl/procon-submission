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

    from math import comb

    ans = []

    a, b, k = map(int, sinput().split())
    top = 1
    length = a + b
    for pos in range(1, length + 1):
        if a == 0:
            ans.append("b")
            continue

        word_num = comb(length - pos, a - 1)
        if k < top + word_num:
            ans.append("a")
            a -= 1
        else:
            ans.append("b")
            top += word_num

    print("".join(ans))


if __name__ == "__main__":
    main()
