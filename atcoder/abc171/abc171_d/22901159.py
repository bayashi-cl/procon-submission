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
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    q = int(sinput())

    ans = sum(a)
    cnt = Counter(a)

    for _ in [None] * q:
        b, c = map(int, sinput().split())
        ans += (c - b) * cnt[b]
        cnt[c] += cnt[b]
        cnt[b] = 0
        print(ans)


if __name__ == "__main__":
    main()
