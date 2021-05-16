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
    _ = sinput()
    a = list(map(int, sinput().split()))
    b = list(map(int, sinput().split()))

    dot = 0
    for ai, bi in zip(a, b):
        dot += ai * bi

    if dot:
        print("No")
    else:
        print("Yes")


if __name__ == "__main__":
    main()
