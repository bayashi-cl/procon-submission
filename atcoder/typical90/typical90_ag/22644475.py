# region template
import sys
import typing
from math import ceil

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    h, w = map(int, sinput().split())
    if h == 1:
        ans = w
    elif w == 1:
        ans = h
    else:
        ans = ceil(h / 2) * ceil(w / 2)
    print(ans)


if __name__ == "__main__":
    main()
