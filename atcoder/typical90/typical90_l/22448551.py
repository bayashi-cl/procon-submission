# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


class UnionFind:
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


def main() -> None:
    h, w = map(int, sinput().split())

    board = [[False] * (w + 2) for _ in range(h + 2)]
    u = UnionFind(h * w)

    def index(r: int, c: int) -> int:
        return (r - 1) * w + (c - 1)

    q = int(sinput())

    for _ in range(q):
        que = list(map(int, sinput().split()))
        if que[0] == 1:
            r, c = que[1:]
            i = index(r, c)
            board[r][c] = True
            if board[r - 1][c]:
                u.unite(i, index(r - 1, c))
            if board[r + 1][c]:
                u.unite(i, index(r + 1, c))
            if board[r][c - 1]:
                u.unite(i, index(r, c - 1))
            if board[r][c + 1]:
                u.unite(i, index(r, c + 1))
        else:
            ra, ca, rb, cb = que[1:]
            if not (board[ra][ca] and board[rb][cb]):
                print("No")
                continue
            if u.same(index(ra, ca), index(rb, cb)):
                print("Yes")
            else:
                print("No")


if __name__ == "__main__":
    main()
