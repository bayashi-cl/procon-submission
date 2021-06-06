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
    n = int(sinput())
    a = list(map(int, sys.stdin.read().split()))
    ma = max(a)
    cnt = Counter(a)
    sec = sorted(a)[-2]
    if cnt[ma] > 1:
        ans = [ma] * n
        print(*ans, sep="\n")
    else:
        ma_idx = a.index(ma)
        for i in range(n):
            if i == ma_idx:
                print(sec)
            else:
                print(ma)


if __name__ == "__main__":
    main()
