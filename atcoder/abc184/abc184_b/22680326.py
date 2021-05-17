# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, x = map(int, sinput().split())
    S = sinput().strip()

    for s in S:
        if s == "o":
            x += 1
        else:
            x = max(0, x - 1)
    print(x)


if __name__ == "__main__":
    main()
