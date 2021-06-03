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
    n, k, m = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    need = max(0, n * m - sum(a))
    if need > k:
        print(-1)
    else:
        print(need)


if __name__ == "__main__":
    main()
