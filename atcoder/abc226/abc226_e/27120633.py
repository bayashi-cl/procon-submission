# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


class UnionFindTree:
    """Union-Find木"""

    def __init__(self, n: int) -> None:
        self.n = n
        self.parent = [-1] * self.n  # 負なら親でありその値は(-子の数)

    def find(self, a: int) -> int:
        now = a
        path = []
        while self.parent[now] >= 0:
            path.append(now)
            now = self.parent[now]
        else:
            root = now

        for p in path:
            self.parent[p] = root

        return root

    def union(self, a: int, b: int) -> bool:
        root_a = self.find(a)
        root_b = self.find(b)

        if root_a == root_b:
            return False

        if -self.parent[root_a] > -self.parent[root_b]:
            root_a, root_b = root_b, root_a
        self.parent[root_b] += self.parent[root_a]
        self.parent[root_a] = root_b

        return True

    def same(self, a: int, b: int):
        return self.find(a) == self.find(b)

    def size(self, a: int) -> int:
        return -self.parent[self.find(a)]

    def group(self) -> Dict[int, List[int]]:
        from collections import defaultdict

        res = defaultdict(list)
        for i in range(self.n):
            res[self.find(i)].append(i)

        return dict(res)


def main() -> None:
    n, m = map(int, sinput().split())
    uft = UnionFindTree(n)
    adj: List[List[int]] = [list() for _ in range(n)]

    for _ in range(m):
        a, b = map(lambda x: int(x) - 1, sinput().split())
        uft.union(a, b)
        adj[a].append(b)

    group = uft.group()
    for _, g in group.items():
        cnt = 0
        for e in g:
            cnt += len(adj[e])
        if cnt != len(g):
            print(0)
            return

    print(pow(2, len(group), MOD))


if __name__ == "__main__":
    main()
