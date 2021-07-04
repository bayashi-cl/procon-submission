# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class WarshallFloyd:
    Edge = Tuple[int, int]  # (cost, node)
    Adj = List[List[Edge]]

    def __init__(self, graph: Adj) -> None:
        self.n_node = len(graph)
        self.cost = [[IINF] * self.n_node for _ in range(self.n_node)]
        for i in range(self.n_node):
            self.cost[i][i] = 0

        for dep, edge in enumerate(graph):
            for dist, arr in edge:
                self.cost[dep][arr] = dist

    def search(self) -> int:
        res = 0
        for k in range(self.n_node):
            for i in range(self.n_node):
                for j in range(self.n_node):
                    dist = self.cost[i][k] + self.cost[k][j]
                    if dist < self.cost[i][j]:
                        self.cost[i][j] = dist
                    if self.cost[i][j] != IINF:
                        res += self.cost[i][j]

        return res


def main() -> None:
    n, m = map(int, sinput().split())
    adj: WarshallFloyd.Adj = [[] for _ in range(n)]
    for _ in range(m):
        a, b, c = map(int, sinput().split())
        adj[a - 1].append((c, b - 1))

    wf = WarshallFloyd(adj)
    print(wf.search())


if __name__ == "__main__":
    main()
