# region template
import sys
import typing
from heapq import heappop, heappush
from collections import deque
from copy import copy

# from itertools import accumulate
# from operator import add

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
    v = deque(map(int, sinput().split()))
    ans = 0
    for l in range(n + 1):
        for r in range(n + 1 - l):

            if l + r > k:
                continue
            que = copy(v)
            hand: Vec = []
            for _ in range(l):
                heappush(hand, que.popleft())
            for _ in range(r):
                heappush(hand, que.pop())

            for _ in range(k - l - r):
                if not hand:
                    break
                p = heappop(hand)
                if p > 0:
                    heappush(hand, p)
                    break
            ans = max(ans, sum(hand))

    print(ans)


if __name__ == "__main__":
    main()
