# region template
import sys
import typing
from heapq import heapify, heappop, heappush
from collections import defaultdict

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
    reward = [tuple(map(int, sinput().split())) for _ in range(n)]
    d = defaultdict(list)
    for a, b in reward:
        d[a].append(b)

    que = []
    ans = 0
    for i in range(1, m + 1):
        for bi in d[i]:
            heappush(que, -bi)
        if que:
            ans += heappop(que)
    print(-ans)


if __name__ == "__main__":
    main()
