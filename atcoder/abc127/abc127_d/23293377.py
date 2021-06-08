# region template
import sys
import typing
from collections import Counter

# from bisect import bisect_left

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

    cnt: Counter = Counter(a)
    for _ in range(m):
        b, c = map(int, sinput().split())
        cnt[c] += b

    deck = []
    for k, v in cnt.items():
        deck.append((k, v))
    deck.sort(reverse=True)

    ans = 0
    card = 0
    for integer, number in deck:
        able = min(number, n - card)
        card += able
        ans += integer * able
        if card >= n:
            break

    print(ans)


if __name__ == "__main__":
    main()
