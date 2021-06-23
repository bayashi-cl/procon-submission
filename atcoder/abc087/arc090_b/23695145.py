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
    Adj = List[List[Tuple[int, int]]]

    def __init__(self, graph: Adj) -> None:
        self.graph: BreadthFirstSearch.Adj = graph
        self.n = len(graph)
        self.cost = [INF] * self.n

    def search(self, start: int) -> bool:
        que = deque([start])
        self.cost[start] = 0

        while que:
            dep = que.popleft()
            for dist, arr in self.graph[dep]:
                if self.cost[arr] == INF:
                    self.cost[arr] = self.cost[dep] + dist
                    que.append(arr)
                else:
                    if self.cost[arr] != self.cost[dep] + dist:
                        return False

        return True


def main() -> None:
    n, m = map(int, sinput().split())

    adj: BreadthFirstSearch.Adj = [[] for _ in range(n)]
    for _ in range(m):
        l, r, d = map(int, sinput().split())
        l -= 1
        r -= 1
        adj[l].append((d, r))
        adj[r].append((-d, l))

    bfs = BreadthFirstSearch(adj)
    for i in range(n):
        if bfs.cost[i] != INF:
            continue
        if bfs.search(i):
            continue
        print("No")
        break
    else:
        print("Yes")


if __name__ == "__main__":
    main()
