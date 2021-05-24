def main() -> None:
    # region template
    import sys
    import typing
    import string

    sys.setrecursionlimit(10 ** 6)
    Vec = typing.List[int]  # noqa:F841
    VecVec = typing.List[Vec]  # noqa:F841
    sinput: typing.Callable[..., str] = sys.stdin.readline  # noqa:F841
    MOD: int = 1000000007  # noqa:F841
    INF: float = float("Inf")  # noqa:F841
    IINF: int = 4611686018427387903  # noqa:F841
    # endregion

    n = int(sinput())
    abc = string.ascii_lowercase
    # n_dog = 1000000000000001
    name = []
    l = 1
    while san(l + 1) <= n:
        l += 1
    top = san(l)
    for i in range(l):
        for j in range(26):
            roop = 26 ** (l - i - 1)
            if top + roop > n:
                name.append(abc[j])
                break
            else:
                top += roop

    print("".join(name))


def san(n: int) -> int:
    return (26 ** n - 26) // 25 + 1


if __name__ == "__main__":
    main()
