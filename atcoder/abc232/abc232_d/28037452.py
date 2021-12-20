# region template
import sys
import typing
from collections import deque
from dataclasses import dataclass
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


class Grid:
    DeltaItr = typing.Iterable[typing.Tuple[int, int]]
    h: int
    w: int

    def __init__(self, h: int, w: int) -> None:
        self.h = h
        self.w = w

    def __contains__(self, ij: typing.Tuple[int, int]) -> bool:
        return 0 <= ij[0] < self.h and 0 <= ij[1] < self.w

    def area(self) -> int:
        return self.h * self.w

    def index(self, i: int, j: int) -> int:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        return self.w * i + j

    def coord(self, ind: int) -> typing.Tuple[int, int]:
        if ind < 0 or self.area() <= ind:
            raise ValueError("index out of grid")
        return divmod(ind, self.w)

    def itergrid(self) -> DeltaItr:
        for i in range(self.h):
            for j in range(self.w):
                yield (i, j)

    def iterdelta(self, i: int, j: int, d: DeltaItr) -> DeltaItr:
        if (i, j) not in self:
            raise ValueError("index out of grid")
        for di, dj in d:
            ni, nj = i + di, j + dj
            if (ni, nj) in self:
                yield (ni, nj)

    def iterdelta2(self, i: int, j: int) -> DeltaItr:
        return self.iterdelta(i, j, ((0, 1), (1, 0)))

    def iterdelta4(self, i: int, j: int) -> DeltaItr:
        return self.iterdelta(i, j, ((-1, 0), (0, 1), (1, 0), (0, -1)))

    def iterdelta8(self, i: int, j: int) -> DeltaItr:
        d = []
        for di in range(-1, 2):
            for dj in range(-1, 2):
                if di == 0 and dj == 0:
                    continue
                d.append((di, dj))
        return self.iterdelta(i, j, d)


@dataclass
class Edge:
    arr: int


@dataclass
class WEdge(Edge):
    arr: int
    cost: int


@dataclass
class DeWEdge(WEdge):
    dep: int
    arr: int
    cost: int

    def __lt__(self, rh: "DeWEdge") -> bool:
        if self.cost is None or rh.cost is None:
            raise ValueError
        return self.cost < rh.cost


T = typing.TypeVar("T", Edge, WEdge, DeWEdge)
Adj = typing.List[typing.List[T]]


class BreadthFirstSearch(typing.Generic[T]):
    INF = sys.maxsize // 2
    graph: Adj[T]
    n_node: int
    cost: typing.List[int]
    prev: typing.List[int]

    def __init__(self, graph: Adj[T], start: int = 0, err_val: int = -1) -> None:
        self.graph = graph
        self.n_node = len(graph)
        if start < 0 or self.n_node <= start:
            raise ValueError("start is out of graph")
        self.cost = [self.INF] * self.n_node
        self.prev = [-1] * self.n_node
        self.search(start)
        for i in range(self.n_node):
            if self.cost[i] == self.INF:
                self.cost[i] = err_val

    def search(self, start: int) -> None:
        que: typing.Deque[int] = deque()
        que.append(start)
        self.cost[start] = 0
        while que:
            now = que.popleft()
            for to in self.graph[now]:
                if self.cost[to.arr] == self.INF:
                    self.cost[to.arr] = self.cost[now] + 1
                    self.prev[to.arr] = now
                    que.append(to.arr)

    def path(self, to: int) -> typing.List[int]:
        if to < 0 or self.n_node <= to:
            raise ValueError("to is out of graph")
        res = []
        while to != -1:
            res.append(to)
            to = self.prev[to]
        return res[::-1]


def main() -> None:
    h, w = map(int, sinput().split())
    grid = Grid(h, w)
    c = [sinput().strip() for _ in range(h)]

    graph: Adj[Edge] = [[] for _ in range(grid.area())]
    for i, j in grid.itergrid():
        if c[i][j] == "#":
            continue
        for ni, nj in grid.iterdelta2(i, j):
            if c[ni][nj] == ".":
                graph[grid.index(i, j)].append(Edge(grid.index(ni, nj)))

    bfs = BreadthFirstSearch(graph)
    print(max(bfs.cost) + 1)


if __name__ == "__main__":
    main()
