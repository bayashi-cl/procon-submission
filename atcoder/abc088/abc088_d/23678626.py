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
    delta_x = (1, -1, 0, 0)
    delta_y = (0, 0, 1, -1)
    h, w = map(int, sinput().split())
    s = [sinput().strip() for _ in range(h)]

    def idx(i: int, j: int) -> int:
        return i * w + j

    adj: VecVec = [[] for _ in range(h * w)]

    white = 0
    for i in range(h):
        for j in range(w):
            if s[i][j] == "#":
                continue
            now = idx(i, j)
            white += 1
            for dx, dy in zip(delta_x, delta_y):
                if i + dx < 0 or h <= i + dx:
                    continue
                if j + dy < 0 or w <= j + dy:
                    continue

                if s[i + dx][j + dy] == ".":
                    adj[now].append(idx(i + dx, j + dy))

    dfs = BreadthFirstSearch(adj)
    cost = dfs.search(0)
    if cost[-1] == INF:
        ans = -1
    else:
        ans = white - cost[-1] - 1

    print(ans)


if __name__ == "__main__":
    main()
