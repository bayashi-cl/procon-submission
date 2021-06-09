# region template
import sys
import typing
from typing import List, Tuple, Union, Optional

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class DepthFirstSearch:
    Adj = List[List[Tuple[int, int]]]

    def __init__(self, graph: Adj) -> None:
        self.n_node = len(graph)
        self.graph = graph
        self.color = [-1] * self.n_node
        self.color[0] = 0

    def search(self, now: int) -> None:
        for to, dist in self.graph[now]:
            if self.color[to] != -1:
                continue
            to_color = self.color[now] ^ dist
            self.color[to] = to_color
            self.search(to)


def main() -> None:
    n = int(sinput())
    adj: DepthFirstSearch.Adj = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v, w = map(int, sinput().split())
        adj[u - 1].append((v - 1, w % 2))
        adj[v - 1].append((u - 1, w % 2))

    dfs = DepthFirstSearch(adj)
    dfs.search(0)
    print(*dfs.color, sep="\n")


if __name__ == "__main__":
    main()
