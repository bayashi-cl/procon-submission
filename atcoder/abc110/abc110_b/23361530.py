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
    n, m, X, Y = map(int, sinput().split())
    x = list(map(int, sinput().split()))
    y = list(map(int, sinput().split()))

    for z in range(max(x) + 1, min(y) + 1):
        if X < z and z <= Y:
            print("No War")
            break
    else:
        print("War")


if __name__ == "__main__":
    main()
