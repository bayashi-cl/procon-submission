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


def main() -> None:
    n, m, k = map(int, sinput().split())

    uft = UnionFindTree(n)
    friend_block = [set() for _ in range(n)]

    friend = [tuple(map(lambda x: int(x) - 1, sinput().split())) for _ in range(m)]
    block = [tuple(map(lambda x: int(x) - 1, sinput().split())) for _ in range(k)]

    for a, b in friend:
        uft.union(a, b)
        friend_block[a].add(b)
        friend_block[b].add(a)

    for c, d in block:
        if uft.same(c, d):
            friend_block[c].add(d)
            friend_block[d].add(c)

    ans = [0] * n
    for i in range(n):
        ans[i] = uft.size(i) - len(friend_block[i]) - 1

    print(*ans)


if __name__ == "__main__":
    main()
