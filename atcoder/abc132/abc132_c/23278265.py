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
    d = list(map(int, sinput().split()))
    d.sort()
    l = d[n // 2 - 1]
    r = d[n // 2]

    print(r - l)


if __name__ == "__main__":
    main()
