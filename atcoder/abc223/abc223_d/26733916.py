# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from heapq import heapify, heappop, heappush


sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    cnt = [0] * n
    adj: List[List[int]] = [list() for _ in range(n)]
    for i in range(m):
        a, b = map(int, sinput().split())
        a -= 1
        b -= 1
        adj[a].append(b)
        cnt[b] += 1

    que: List[int] = []
    for i, x in enumerate(cnt):
        if x == 0:
            que.append(i)
    heapify(que)

    ans: List[int] = []
    while que:
        top = heappop(que)
        ans.append(top)
        for to in adj[top]:
            cnt[to] -= 1
            if cnt[to] == 0:
                heappush(que, to)

    if len(ans) != n:
        print(-1)
    else:
        print(*map(lambda x: x + 1, ans))
        # print(*ans)


if __name__ == "__main__":
    main()
