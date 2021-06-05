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
    a = int(sinput())
    s = sinput().strip()
    if a >= 3200:
        print(s)
    else:
        print("red")


if __name__ == "__main__":
    main()
