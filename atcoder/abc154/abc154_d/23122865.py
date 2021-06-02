# region template
import sys
import typing
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
    p = list(map(int, sinput().split()))
    ep = [0.0] * (n + 1)
    for i in range(n):
        ep[i + 1] = (p[i] + 1) / 2

    ep = list(accumulate(ep))
    ans = 0.0
    for i in range(k, n + 1):
        ans = max(ans, ep[i] - ep[i - k])

    print(ans)


if __name__ == "__main__":
    main()
