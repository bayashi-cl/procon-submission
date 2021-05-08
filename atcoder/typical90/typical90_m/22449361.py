# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
import heapq


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def dijkstra(start: int, n_node: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    beta_root = [(0, start)]
    heapq.heapify(beta_root)
    cost = [INF] * n_node
    cost[start] = 0
    while beta_root:
        beta_cost, beta_node = heapq.heappop(beta_root)
        if beta_cost > cost[beta_node]:
            continue
        for adj_cost, adj_node in adj[beta_node]:
            temp_cost = cost[beta_node] + adj_cost
            if temp_cost < cost[adj_node]:
                cost[adj_node] = temp_cost
                heapq.heappush(beta_root, (temp_cost, adj_node))
    return cost


def main() -> None:
    n, m = map(int, sinput().split())
    adj = [[] for _ in range(n)]
    for _ in range(m):
        a, b, c = map(int, sinput().split())
        a -= 1
        b -= 1
        adj[a].append((c, b))
        adj[b].append((c, a))

    from1 = dijkstra(0, n, adj)
    fromn = dijkstra(n - 1, n, adj)

    for i, j in zip(from1, fromn):
        print(i + j)


if __name__ == "__main__":
    main()
