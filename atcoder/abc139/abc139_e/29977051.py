import sys
from collections import defaultdict, deque
from itertools import combinations
from typing import DefaultDict, List, Tuple, Deque, Dict

# from byslib.core.const import IINF, MOD
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.const = ModuleType("byslib.core.const")

_code_byslib = """
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.1"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core = """

"""
exec(_code_byslib_core, byslib.core.__dict__)

_code_byslib_core_const = """
import sys

MOD: int = 998244353
MOD7: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
"""
exec(_code_byslib_core_const, byslib.core.const.__dict__)

IINF = byslib.core.const.IINF
MOD = byslib.core.const.MOD
# from byslib.core.io import debug, readline, sinput, int1
byslib.core.io = ModuleType("byslib.core.io")

_code_byslib_core_io = """
import sys
from functools import partial

readline = sys.stdin.buffer.readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: str) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_io, byslib.core.io.__dict__)

debug = byslib.core.io.debug
readline = byslib.core.io.readline
sinput = byslib.core.io.sinput
int1 = byslib.core.io.int1


def main() -> None:
    n = int(readline())
    a: List[List[int]] = [list(map(int1, readline().split())) for _ in range(n)]
    sz = n * (n - 1) // 2
    deg = [0] * sz
    graph: List[List[int]] = [[] for _ in range(sz)]
    index: Dict[Tuple[int, int], int] = dict()
    for idx, ij in enumerate(combinations(range(n), 2)):
        index[ij] = idx

    for i in range(n):
        for j in range(n - 2):
            f = a[i][j]
            if i < f:
                src = i, f
            else:
                src = f, i
            t = a[i][j + 1]
            if i < t:
                dest = i, t
            else:
                dest = t, i
            deg[index[dest]] += 1
            graph[index[src]].append(index[dest])

    que: Deque[int] = deque()
    for i, di in enumerate(deg):
        if di == 0:
            que.append(i)

    topo = []
    while que:
        top = que.popleft()
        topo.append(top)
        for nxt in graph[top]:
            deg[nxt] -= 1
            if deg[nxt] == 0:
                que.append(nxt)

    if len(topo) != sz:
        print(-1)
        return

    dp = [0] * sz
    for now in reversed(topo):
        if graph[now]:
            dp[now] = max(dp[nxt] for nxt in graph[now]) + 1
        else:
            dp[now] = 1
    print(max(dp))


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
