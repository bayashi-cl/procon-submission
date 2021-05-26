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
    a, b, c, d = map(int, sinput().split())
    while True:
        c -= b
        if c <= 0:
            print("Yes")
            break

        a -= d
        if a <= 0:
            print("No")
            break


if __name__ == "__main__":
    main()
