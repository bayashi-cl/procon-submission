# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import deque

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class BreadthFirstSearch:
    def __init__(self, graph: VecVec) -> None:
        self.graph = graph
        self.n = len(graph)

    def search(self, start: int) -> typing.List[typing.Union[float, int]]:
        que = deque([start])
        self.cost = [INF] * self.n
        self.cost[start] = 0

        while que:
            dep = que.popleft()
            for arr in self.graph[dep]:
                if self.cost[arr] == INF:
                    self.cost[arr] = self.cost[dep] + 1
                    que.append(arr)

        return self.cost


def main() -> None:
    n, q = map(int, sinput().split())
    adj: VecVec = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = map(int, sinput().split())
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    bfs = BreadthFirstSearch(adj)
    cost = bfs.search(0)

    for _ in range(q):
        c, d = map(int, sinput().split())
        if (cost[c - 1] + cost[d - 1]) % 2 == 0:
            print("Town")
        else:
            print("Road")


if __name__ == "__main__":
    main()
