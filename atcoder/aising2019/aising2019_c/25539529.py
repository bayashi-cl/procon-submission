# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
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

    def group(self) -> Dict[int, Set[int]]:
        from collections import defaultdict

        res = defaultdict(set)
        for i in range(self.n):
            res[self.find(i)].add(i)

        return dict(res)


def main() -> None:
    h, w = map(int, sinput().split())
    s = [sinput().strip() for _ in range(h)]
    delta = ((1, 0), (0, 1))

    def idx(i: int, j: int) -> int:
        return w * i + j

    uft = UnionFindTree(h * w)

    for i in range(h):
        for j in range(w):
            for di, dj in delta:
                ni = i + di
                nj = j + dj
                if ni >= h or nj >= w:
                    continue

                if s[i][j] == "#":
                    if s[ni][nj] == ".":
                        uft.union(idx(i, j), idx(ni, nj))
                else:
                    if s[ni][nj] == "#":
                        uft.union(idx(i, j), idx(ni, nj))

    cnt = [[0, 0] for _ in range(h * w)]
    for i in range(h):
        for j in range(w):
            p = uft.find(idx(i, j))
            if s[i][j] == "#":
                cnt[p][0] += 1
            else:
                cnt[p][1] += 1

    ans = 0
    for b, w in cnt:
        ans += b * w
    print(ans)


if __name__ == "__main__":
    main()
