# region template
import sys
import typing
from statistics import mean

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    x = list(map(int, sinput().split()))
    p = round(mean(x))
    s = 0
    for i in x:
        s += (i - p) ** 2

    print(s)


if __name__ == "__main__":
    main()
