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

    _ = int(sinput())
    res = sys.stdin.read().strip().split()

    ac = res.count("AC")
    wa = res.count("WA")
    tle = res.count("TLE")
    re = res.count("RE")

    print(f"AC x {ac}")
    print(f"WA x {wa}")
    print(f"TLE x {tle}")
    print(f"RE x {re}")


if __name__ == "__main__":
    main()
