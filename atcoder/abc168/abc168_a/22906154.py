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

    o = n % 10

    if o == 3:
        print("bon")
    elif o in [0, 1, 6, 8]:
        print("pon")
    else:
        print("hon")


if __name__ == "__main__":
    main()
