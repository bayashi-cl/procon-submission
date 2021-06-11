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
    d = int(sinput())
    if d == 25:
        print("Christmas")
    elif d == 24:
        print("Christmas Eve")
    elif d == 23:
        print("Christmas Eve Eve")
    elif d == 22:
        print("Christmas Eve Eve Eve")


if __name__ == "__main__":
    main()
