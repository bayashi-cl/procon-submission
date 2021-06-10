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
    H, W = map(int, sinput().split())
    h, w = map(int, sinput().split())
    print((H - h) * (W - w))


if __name__ == "__main__":
    main()
