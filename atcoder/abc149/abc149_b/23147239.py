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
    a, b, k = map(int, sinput().split())
    if k >= a:
        print(0, max(0, b - (k - a)))
    else:
        print(a - k, b)


if __name__ == "__main__":
    main()
