# region template
import sys
import typing
from math import floor

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, n = map(int, sinput().split())
    ans = -INF

    def f(x):
        res = (a * x) // b - a * (x // b)
        return res

    ans = f(n)
    if b - 1 <= n:
        ans = max(f(b - 1), ans)

    print(ans)


if __name__ == "__main__":
    main()
