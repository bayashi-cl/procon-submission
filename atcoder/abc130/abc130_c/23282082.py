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
    w, h, x, y = map(int, sinput().split())
    ans = w * h / 2
    if 2 * x == w and 2 * y == h:
        print(ans, 1)
    else:
        print(ans, 0)


if __name__ == "__main__":
    main()
