# region template
import sys
import typing
from collections import Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    a[0] %= m
    for i in range(1, n):
        a[i] += a[i - 1]
        a[i] %= m

    cnt = Counter(a)
    cnt[0] += 1
    ans = 0
    for v in cnt.values():
        ans += v * (v - 1) // 2

    print(ans)


if __name__ == "__main__":
    main()
