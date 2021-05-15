# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, c = map(int, sinput().split())
    if a ** 2 + b ** 2 < c ** 2:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
