# region template
import sys
import typing
from bisect import bisect_left
from itertools import accumulate

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    cs = list(accumulate(a))

    ans = 0
    for i in range(n):
        if i == 0:
            left_sum = 0
        else:
            left_sum = cs[i - 1]

        ans += n - bisect_left(cs, k + left_sum)

    print(ans)


if __name__ == "__main__":
    main()
