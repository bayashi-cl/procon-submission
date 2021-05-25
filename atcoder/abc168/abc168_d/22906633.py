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


def bfs(adj: typing.List[typing.List[int]], start: int, n_node: int):
    q = deque([start])
    cost = [float("inf")] * n_node
    cost[start] = 0
    before = [-1] * n_node
    while q:
        node_from = q.popleft()
        for node_to in adj[node_from]:
            if cost[node_to] == float("inf"):
                cost[node_to] = cost[node_from] + 1
                before[node_to] = node_from
                q.append(node_to)
    return cost, before


def main() -> None:
    n, m = map(int, sinput().split())
    adj = [[] for _ in range(n + 1)]
    for _ in [None] * m:
        a, b = map(int, sinput().split())
        adj[a].append(b)
        adj[b].append(a)

    cost, before = bfs(adj, 1, n + 1)

    if INF in cost[1:]:
        print("No")
    else:
        print("Yes")
        print(*before[2:], sep="\n")


if __name__ == "__main__":
    main()
