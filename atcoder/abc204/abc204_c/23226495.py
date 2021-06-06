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
    n, m = map(int, sinput().split())
    adj = [[] for _ in range(n)]
    for i in range(m):
        a, b = map(int, sinput().split())
        adj[a - 1].append(b - 1)

    bfs = BreadthFirstSearch(adj)
    ans = 0
    for i in range(n):
        cost = bfs.search(i)
        for c in cost:
            if c != INF:
                ans += 1

    print(ans)


if __name__ == "__main__":
    main()
