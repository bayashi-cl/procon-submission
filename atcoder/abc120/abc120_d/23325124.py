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
    bridge = [list(map(lambda x: int(x) - 1, sinput().split())) for _ in range(m)]

    uft = UnionFindTree(n)
    unuse = n * (n - 1) // 2
    ans = [unuse]
    for a, b in reversed(bridge):
        if uft.same(a, b):
            ans.append(unuse)
        else:
            unuse -= uft.size(a) * uft.size(b)
            uft.union(a, b)
            ans.append(unuse)

    # print(ans, file=sys.stderr)
    print("\n".join(map(str, reversed(ans[-2 - m : -1]))))


if __name__ == "__main__":
    main()
