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

    n = sinput().strip()
    m3 = [int(d) % 3 for d in n]
    s = sum(m3) % 3

    zero = m3.count(0)
    one = m3.count(1)
    two = m3.count(2)

    if s == 0:
        ans = 0
    elif s == 1:
        if one:
            if one > 1 or two or zero:
                ans = 1
            else:
                ans = -1
        else:
            if two > 2:
                ans = 2
            elif two == 2 and zero:
                ans = 2
            else:
                ans = -1
    else:
        if two:
            if two > 1 or one or zero:
                ans = 1
            else:
                ans = -1
        else:
            if one > 2:
                ans = 2
            elif one == 2 and zero:
                ans = 2
            else:
                ans = -1
    print(ans)


if __name__ == "__main__":
    main()
