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
    x = int(sinput())
    m = 100
    y = 0
    while m < x:
        m += m // 100
        y += 1
    print(y)


if __name__ == "__main__":
    main()
