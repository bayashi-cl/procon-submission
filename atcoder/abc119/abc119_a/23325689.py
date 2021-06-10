# region template
import sys
import typing
import datetime

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    s = datetime.date(*map(int, sinput().split("/")))
    if s <= datetime.date(2019, 4, 30):
        print("Heisei")
    else:
        print("TBD")


if __name__ == "__main__":
    main()
