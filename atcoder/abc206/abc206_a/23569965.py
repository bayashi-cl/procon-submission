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
    n = int(sinput())
    t = int(n * 1.08)
    if t < 206:
        print("Yay!")
    elif t == 206:
        print("so-so")
    else:
        print(":(")


if __name__ == "__main__":
    main()
