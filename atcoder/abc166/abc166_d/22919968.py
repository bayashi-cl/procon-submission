# region template
import sys
import typing
import math

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    x = int(sinput())

    for a in range(-200, 200):
        for b in range(-200, 200):
            if a ** 5 - b ** 5 == x:
                print(a, b)
                return


if __name__ == "__main__":
    main()
