# region template
import sys
import typing

from collections import deque, Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class DepthFirstSearch:
    def __init__(self, graph: VecVec, color):
        self.graph = graph
        # self.pre_order: Vec = []
        self.seen = [False] * len(graph)
        # self.post_orfer: Vec = []
        self.color = color
        self.is_good = [False] * len(graph)
        self.palette = Counter()

    def search(self, now: int):
        self.seen[now] = True
        if self.palette[self.color[now]] == 0:
            self.is_good[now] = True
        self.palette[self.color[now]] += 1

        # self.pre_order.append(now)
        for to in self.graph[now]:
            if self.seen[to]:
                continue
            self.search(to)
        # self.post_orfer.append(now)

        self.palette[self.color[now]] -= 1


def main() -> None:
    n = int(sinput())
    c = list(map(int, sinput().split()))

    adj: VecVec = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = map(int, sinput().split())
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    bfs = DepthFirstSearch(adj, c)
    bfs.search(0)

    ans = []
    for i in range(n):
        if bfs.is_good[i]:
            ans.append(i + 1)

    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
