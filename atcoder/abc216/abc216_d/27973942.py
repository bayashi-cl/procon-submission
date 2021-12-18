# region template
import sys
import typing
from collections import deque
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    graph: List[List[int]] = [[] for _ in range(n)]
    deg = [0] * n
    for _ in range(m):
        k = int(sinput())
        a = tuple(map(lambda x: int(x) - 1, sinput().split()))
        if len(set(a)) != k:
            print("No")
            return
        for i in range(k - 1):
            deg[a[i + 1]] += 1
            graph[a[i]].append(a[i + 1])

    que: typing.Deque[int] = deque()
    for i, di in enumerate(deg):
        if di == 0:
            que.append(i)

    while que:
        now = que.popleft()
        for to in graph[now]:
            deg[to] -= 1
            if deg[to] == 0:
                que.append(to)

    if all(di == 0 for di in deg):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
