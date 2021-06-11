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
    n = sinput().strip()
    n = n.replace("9", "x")
    n = n.replace("1", "9")
    n = n.replace("x", "1")

    print(n)


if __name__ == "__main__":
    main()
