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
    k, x = map(int, sinput().split())
    lo = max(-1000000, x - k + 1)
    hi = min(1000000, x + k - 1)
    print(*range(lo, hi + 1))


if __name__ == "__main__":
    main()
