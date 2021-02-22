import heapq
from typing import List, Tuple

INF: int = 10 ** 9


def edge2adj(edge: List[List[int]], n_node: int) -> List[List[Tuple[int, int]]]:
    adj: List[List[Tuple[int, int]]] = [[] for _ in range(n_node)]
    edge_dict = dict()

    for start, end, cost in edge:
        start -= 1
        end -= 1
        if ((start, end) in edge_dict) and edge_dict[(start, end)] < cost:
            continue
        edge_dict[(start, end)] = cost
        adj[start].append((cost, end))
    return adj


n, m = map(int, input().split())
ans = [-1] * n
edge = [list(map(int, input().split())) for _ in range(m)]
adj = edge2adj(edge, n)

for i in range(n):
    # beta_root = [(0, start)]
    # heapq.heapify(beta_root)
    # cost[start] = 0
    beta_root: List[Tuple[int, int]] = []
    cost = [INF] * n
    for sc, sn in adj[i]:
        heapq.heappush(beta_root, (sc, sn))
        cost[sn] = sc

    while beta_root:
        beta_cost, beta_node = heapq.heappop(beta_root)
        if beta_node == i:
            ans[i] = beta_cost
            break
        if beta_cost > cost[beta_node]:
            continue
        for adj_cost, adj_node in adj[beta_node]:
            temp_cost = cost[beta_node] + adj_cost
            if temp_cost < cost[adj_node]:
                cost[adj_node] = temp_cost
                heapq.heappush(beta_root, (temp_cost, adj_node))

for a in ans:
    print(a)
