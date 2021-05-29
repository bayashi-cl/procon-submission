# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    _ = int(sinput())
    A = list(map(int, sinput().split()))
    ok = True
    for a in A:
        if a % 2 == 0:
            if a % 3 != 0 and a % 5 != 0:
                ok = False

    if ok:
        print("APPROVED")
    else:
        print("DENIED")


if __name__ == "__main__":
    main()
