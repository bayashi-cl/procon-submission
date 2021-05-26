# region template
import sys
import typing
import heapq
from math import ceil


sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class Dijkstra:
    """ダイクストラ法による最短経路探索
    * O(N + MlogN)
    """

    # 隣接グラフ(cost, node)
    Adj = typing.List[typing.List[typing.Tuple[int, int, int]]]
    INF = float("inf")
    sinput = sys.stdin.readline

    def __init__(self, graph: Adj):
        self.n_node = len(graph)
        self.graph = graph

    def search(self, start: int) -> typing.List[float]:
        self.cost = [self.INF] * self.n_node
        self.cost[start] = 0
        self.prev = [-1] * self.n_node
        que: typing.List[typing.Tuple[float, int]] = [(0, start)]
        heapq.heapify(que)

        while que:
            top_cost, top_node = heapq.heappop(que)
            if top_cost > self.cost[top_node]:
                continue
            for adj_cost, adj_node, k in self.graph[top_node]:
                temp_cost = (ceil(self.cost[top_node] / k)) * k + adj_cost

                if temp_cost < self.cost[adj_node]:
                    self.cost[adj_node] = temp_cost
                    heapq.heappush(que, (temp_cost, adj_node))
                    self.prev[adj_node] = top_node

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
            if index != 0:
                f -= index
                t -= index
            adj[f].append((c, t))
            if not direction:
                adj[t].append((c, f))

        return cls(adj)


def main() -> None:
    n, m, x, y = map(int, sinput().split())

    adj: Dijkstra.Adj = [[] for _ in range(n)]

    for i in range(m):
        a, b, t, k = map(int, sinput().split())
        adj[a - 1].append((t, b - 1, k))
        adj[b - 1].append((t, a - 1, k))

    dij = Dijkstra(adj)
    ans = dij.search(x - 1)[y - 1]
    if ans == INF:
        ans = -1

    print(ans)


if __name__ == "__main__":
    main()
