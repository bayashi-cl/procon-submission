# region template
import sys
import typing
from collections import defaultdict

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
        self.tree = [-1] * n
        self.rank = [-1] * n

    def find(self, x: int) -> int:
        if x >= self.n:
            raise ValueError
        if self.tree[x] == -1:
            return x
        else:
            self.tree[x] = self.find(self.tree[x])
            return self.tree[x]

    def unite(self, x: int, y: int) -> bool:
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        if self.rank[x] > self.rank[y]:
            x, y = y, x
        elif self.rank[x] > self.rank[y]:
            self.rank[y] += 1
        self.tree[x] = y
        return True

    def same(self, x: int, y: int) -> bool:
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return True
        else:
            return False

    def group(self):
        res = defaultdict(int)
        for i in range(self.n):
            res[self.find(i)] += 1
        return dict(res)


def main() -> None:
    n, m, k = map(int, sinput().split())

    uft = UnionFindTree(n)
    friend_block = [set() for _ in range(n)]

    friend = [tuple(map(lambda x: int(x) - 1, sinput().split())) for _ in range(m)]
    block = [tuple(map(lambda x: int(x) - 1, sinput().split())) for _ in range(k)]

    for a, b in friend:
        uft.unite(a, b)
        friend_block[a].add(b)
        friend_block[b].add(a)

    chain = uft.group()

    for c, d in block:
        if uft.same(c, d):
            friend_block[c].add(d)
            friend_block[d].add(c)

    ans = [0] * n
    for i in range(n):
        ans[i] = chain[uft.find(i)] - len(friend_block[i]) - 1

    print(*ans)


if __name__ == "__main__":
    main()
