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
    a = list(map(int, sinput().split()))
    if sum(a) >= 22:
        print("bust")
    else:
        print("win")


if __name__ == "__main__":
    main()
