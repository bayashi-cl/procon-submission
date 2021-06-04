# region template
import sys
import typing
from collections import deque

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class DepthFirstSearchM:
    """"""

    def __init__(self, graph: list):
        self.graph = graph
        self.pre_order: Vec = []
        self.seen = [False] * len(graph)
        self.color = [0] * (len(graph) - 1)

    def search(self, start: int):
        que = deque([(start, 0)])
        self.seen[start] = True

        while que:
            now, par_c = que.pop()
            self.pre_order.append(now)
            c = 1

            for i, to in self.graph[now]:
                if self.seen[to]:
                    continue
                self.seen[to] = True
                if c == par_c:
                    c += 1
                self.color[i] = c
                que.append((to, c))
                c += 1


def main() -> None:
    n = int(sinput())
    adj = [set() for _ in range(n)]
    edge = [tuple(map(int, sinput().split())) for _ in range(n)]
    for i in range(n - 1):
        a, b = edge[i]
        adj[a - 1].add((i, b - 1))
        adj[b - 1].add((i, a - 1))

    k = 0
    for ad in adj:
        k = max(k, len(ad))
    dfs = DepthFirstSearchM(adj)
    dfs.search(0)

    print(k)
    print(*dfs.color, sep="\n")


if __name__ == "__main__":
    main()
