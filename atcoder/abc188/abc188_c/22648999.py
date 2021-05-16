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
    n = int(sinput())
    a = list(map(int, sinput().split()))
    m = 2 ** n // 2
    left = max(a[:m])
    right = max(a[m:])
    if left < right:
        print(a.index(left) + 1)
    else:
        print(a.index(right) + 1)


if __name__ == "__main__":
    main()
