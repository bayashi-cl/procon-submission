# region template
import sys
import typing
from itertools import accumulate

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
    a.sort(reverse=True)

    cs = list(accumulate(a))
    ans = 0
    for i in range(n - 1):
        j = cs[-1] - cs[i]
        ans += (n - i - 1) * a[i] - j
    print(ans)


if __name__ == "__main__":
    main()
