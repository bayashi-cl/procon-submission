# region template
import sys
import typing
from statistics import median

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
    a = list(map(int, sinput().split()))

    for i in range(n):
        a[i] -= i + 1
    a.sort()

    def f(x):
        res = 0
        for ai in a:
            res += abs(ai - x)
        return res

    ans = f(int(median(a)))
    print(ans)


if __name__ == "__main__":
    main()
