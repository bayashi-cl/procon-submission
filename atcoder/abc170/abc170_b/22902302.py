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
    x, y = map(int, sinput().split())

    if y % 2 == 0 and y >= 2 * x and y <= 4 * x:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
