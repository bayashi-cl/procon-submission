# region template
import sys
from typing import Callable, List


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


class DFS:
    def __init__(self, graph: List[List[int]]):
        self.graph = graph
        self.col = [0] * len(graph)

    def search(self, now: int, before: int = -1):
        if before == -1:
            self.col[now] = 2
        else:
            self.col[now] = 3 - self.col[before]
        for to in self.graph[now]:
            if to == before:
                continue
            self.search(to, now)


def main() -> None:
    n = int(sinput())
    graph: List[List[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = map(int, sinput().split())
        graph[a].append(b)
        graph[b].append(a)

    d = DFS(graph)
    d.search(1)

    one = []
    two = []
    for i in range(1, n + 1):
        if d.col[i] == 2:
            one.append(i)
        else:
            two.append(i)

    if len(one) >= n // 2:
        print(" ".join(map(str, one[: n // 2])))
    else:
        print(" ".join(map(str, two[: n // 2])))


if __name__ == "__main__":
    main()
