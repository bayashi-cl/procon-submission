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
    a, b, c = map(int, sinput().split())
    if c % 2 == 0:

        a = abs(a)
        b = abs(b)
    if a < b:
        print("<")
    elif a == b:
        print("=")
    else:
        print(">")


if __name__ == "__main__":
    main()
