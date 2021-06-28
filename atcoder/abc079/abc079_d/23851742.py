# region template
import sys
import typing
import heapq
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter
from itertools import chain

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class Dijkstra:
    """ダイクストラ法による最短経路探索
    import heapq
    * O(N + M * logN)
    """

    # 隣接グラフ(cost, node)
    Edge = typing.Tuple[float, int]
    Adj = typing.List[typing.List[Edge]]
    INF = float("inf")
    sinput = sys.stdin.readline

    def __init__(self, graph: Adj):
        self.graph = graph
        self.n_node = len(graph)

    def search(self, start: int) -> typing.List[float]:
        self.cost = [Dijkstra.INF] * self.n_node
        self.cost[start] = 0
        que: typing.List[Dijkstra.Edge] = [(0, start)]
        self.prev = [-1] * self.n_node

        while que:
            top_cost, top_node = heapq.heappop(que)

            if top_cost > self.cost[top_node]:
                continue

            for adj_cost, adj_node in self.graph[top_node]:
                temp_cost = self.cost[top_node] + adj_cost

                if temp_cost < self.cost[adj_node]:
                    self.cost[adj_node] = temp_cost
                    self.prev[adj_node] = top_node
                    heapq.heappush(que, (temp_cost, adj_node))

        return self.cost


def main() -> None:
    h, w = map(int, sinput().split())
    c = [tuple(map(int, sinput().split())) for _ in range(10)]
    a = [tuple(map(int, sinput().split())) for _ in range(h)]
    adj: Dijkstra.Adj = [[] for _ in range(10)]
    for i in range(10):
        for j in range(10):
            if i == j:
                continue
            adj[i].append((c[i][j], j))

    dij = Dijkstra(adj)
    cost = dict()
    for dep in range(10):
        cost[dep] = dij.search(dep)[1]
    cnt = Counter(chain.from_iterable(a))
    ans = 0
    for k, v in cnt.items():
        if k == -1:
            continue
        ans += cost[k] * v
    print(ans)


if __name__ == "__main__":
    main()
