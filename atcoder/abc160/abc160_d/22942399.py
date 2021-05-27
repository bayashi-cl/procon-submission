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

    def search(self, start: int) -> typing.List[int]:
        que = deque([start])
        self.cost = [IINF] * self.n
        self.cost[start] = 0

        while que:
            dep = que.popleft()
            for arr in self.graph[dep]:
                if self.cost[arr] == IINF:
                    self.cost[arr] = self.cost[dep] + 1
                    que.append(arr)

        return self.cost


def main() -> None:
    n, x, y = map(int, sinput().split())

    graph = [[i - 1, i + 1] for i in range(n)]
    graph[0] = [1]
    graph[-1] = [n - 2]
    # print(graph)
    graph[x - 1].append(y - 1)
    graph[y - 1].append(x - 1)

    cnt = [0] * n
    bfs = BreadthFirstSearch(graph)
    for i in range(n):
        cost = bfs.search(i)
        for c in cost:
            cnt[c] += 1

    ans = [c // 2 for c in cnt[1:]]

    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
