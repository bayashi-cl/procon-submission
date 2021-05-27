# region template
import sys
import typing
from collections import Counter
from math import comb

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

    cnt = Counter(a)
    base = 0
    for c in cnt.values():
        base += comb(c, 2)

    for k in range(n):
        b = cnt[a[k]]
        if b == 0:
            print(base)
            continue
        ans = base - comb(b, 2) + comb(b - 1, 2)
        print(ans)


if __name__ == "__main__":
    main()
