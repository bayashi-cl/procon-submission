# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
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

    def group(self):
        from collections import defaultdict

        res = defaultdict(set)
        for i in range(self.n):
            res[self.find(i)].add(i)

        return dict(res)


def main() -> None:
    n, m = map(int, sinput().split())
    p = list(map(lambda x: int(x) - 1, sinput().split()))
    uft = UnionFindTree(n)
    for _ in range(m):
        x, y = map(lambda x: int(x) - 1, sinput().split())
        uft.union(x, y)

    joint = uft.group()
    ans = 0
    for val in joint.values():
        s = set()
        for v in val:
            s.add(p[v])
        ans += len(s & val)
    print(ans)


if __name__ == "__main__":
    main()
