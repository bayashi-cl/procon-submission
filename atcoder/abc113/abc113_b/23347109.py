# region template
import sys
import typing
from bisect import bisect


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
    t, a = map(int, sinput().split())
    h = list(map(lambda x: t - int(x) * 0.006, sinput().split()))

    diff = INF
    ans = -1
    for i, hi in enumerate(h):
        if (d := abs(a - hi)) < diff:
            diff = d
            ans = i

    print(ans + 1)


if __name__ == "__main__":
    main()
