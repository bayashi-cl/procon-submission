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

    def make_divisors(n):
        lower, upper = [], []
        i = 1
        while i * i <= n:
            if n % i == 0:
                lower.append(i)
                if i != n // i:
                    upper.append(n // i)
            i += 1
        return lower + upper[::-1]

    n = int(sinput())
    print(*make_divisors(n), sep="\n")


if __name__ == "__main__":
    main()
