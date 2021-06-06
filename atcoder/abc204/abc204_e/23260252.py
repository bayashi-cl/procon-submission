# region template
import sys
import typing
import heapq
from math import sqrt

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
    import heapq
    * O(N**2)
    """

    # 隣接グラフ(cost, node)
    Adj = typing.List[typing.List[typing.Tuple[int, int, int]]]
    INF = float("inf")
    sinput = sys.stdin.readline

    def __init__(self, n_node: int, graph: Adj):
        self.n_node = n_node
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
            for c, d, adj_node in self.graph[top_node]:
                sq = int(sqrt(d))
                t = [s for s in (sq - 1, sq, sq + 1, top_cost) if s >= top_cost]
                temp_cost = min(i + c + d // (i + 1) for i in t)

                if temp_cost < self.cost[adj_node]:
                    self.cost[adj_node] = temp_cost
                    heapq.heappush(que, (temp_cost, adj_node))
                    self.prev[adj_node] = top_node

        return self.cost


def main() -> None:
    n, m = map(int, sinput().split())
    adj = [[] for _ in range(n)]
    for i in range(m):
        a, b, c, d = map(int, sinput().split())
        adj[a - 1].append((c, d, b - 1))
        adj[b - 1].append((c, d, a - 1))

    dij = Dijkstra(n, adj)
    ans = dij.search(0)[n - 1]
    if ans == INF:
        ans = -1
    print(ans)


if __name__ == "__main__":
    main()
