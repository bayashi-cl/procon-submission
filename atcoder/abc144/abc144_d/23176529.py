# region template
import sys
import typing
from math import degrees, atan2

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, x = map(int, sinput().split())
    r = a ** 2 * b - x

    if r <= x:
        theta = atan2(2 * r, a ** 3)
    else:
        theta = atan2(a * b ** 2, 2 * x)
    print(degrees(theta))


if __name__ == "__main__":
    main()
