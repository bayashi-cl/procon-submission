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
NAN = float("nan")


class BreadthFirstSearch:
    def __init__(self, graph: VecVec) -> None:
        self.graph = graph
        self.n = len(graph)

    def search(self, start: int) -> typing.List[typing.Union[float, int]]:
        que = deque([start])
        self.cost = [-1] * self.n
        self.cost[start] = 0

        while que:
            dep = que.popleft()
            for arr in self.graph[dep]:
                if self.cost[arr] == -1:
                    self.cost[arr] = self.cost[dep] + 1
                    que.append(arr)

        return self.cost


def main() -> None:

    h, w = map(int, sinput().split())

    def index(i, j):
        return i * w + j

    # False: wall, True: load
    s = [[False] * (w + 1) for _ in range(h + 1)]
    for i in range(h):
        line = sinput().strip()
        for j in range(w):
            if line[j] == ".":
                s[i][j] = True

    adj: VecVec = [[] for _ in range(h * w)]

    dx = [-1, 0, 0, 1]
    dy = [0, -1, 1, 0]
    for i in range(h):
        for j in range(w):
            if not s[i][j]:
                continue
            for x, y in zip(dx, dy):
                if s[i + y][j + x]:
                    adj[index(i, j)].append(index(i + y, j + x))

    bfs = BreadthFirstSearch(adj)
    ans = -1
    for i in range(h):
        for j in range(w):
            if s[i][j]:
                cost = bfs.search(index(i, j))
                ans = max(ans, max(cost))

    print(ans)


if __name__ == "__main__":
    main()
