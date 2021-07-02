# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
import heapq

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

    def path_finder(self, to: int) -> typing.List[int]:
        assert to <= self.n_node

        path = []
        while to != -1:
            path.append(to)
            to = self.prev[to]

        return path[::-1]

    @classmethod
    def read(
        cls, n_node: int, n_edge: int, direction: bool = False, index: int = 1
    ) -> "Dijkstra":
        """
        (from, to, cost) の形式で標準入力から読み取り
        """

        adj: Dijkstra.Adj = [[] for _ in range(n_node)]

        for _ in range(n_edge):
            f, t, c = map(int, cls.sinput().split())
            f -= index
            t -= index

            adj[f].append((c, t))
            if not direction:
                adj[t].append((c, f))

        return cls(adj)


def main() -> None:
    n = int(sinput())
    dij = Dijkstra.read(n, n - 1)

    q, k = map(int, sinput().split())

    cost = dij.search(k - 1)

    for _ in range(q):
        x, y = map(int, sinput().split())
        print(cost[x - 1] + cost[y - 1])


if __name__ == "__main__":
    main()
