# region template
import sys
import typing
from math import pi

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    r = float(sinput())
    print(2 * r * pi)


if __name__ == "__main__":
    main()
