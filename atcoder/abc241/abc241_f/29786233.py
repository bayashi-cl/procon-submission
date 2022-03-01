import sys
from bisect import bisect_left
from collections import defaultdict, deque
from typing import DefaultDict, Deque, Dict, List, Tuple

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
# from byslib.core.io import debug, int1, readline, sinput
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
int1 = byslib.core.io.int1
readline = byslib.core.io.readline
sinput = byslib.core.io.sinput


def main() -> None:
    Pos = Tuple[int, int]

    h, w, n = map(int, readline().split())
    si, sj = map(int1, readline().split())
    gi, gj = map(int1, readline().split())
    rock = [tuple(map(int1, readline().split())) for _ in range(n)]

    row: DefaultDict[int, List[int]] = defaultdict(list)
    col: DefaultDict[int, List[int]] = defaultdict(list)

    for i, j in rock:
        row[i].append(j)
        col[j].append(i)
    for e in row:
        row[e].sort()
    for e in col:
        col[e].sort()

    que: Deque[Pos] = deque()
    que.append((si, sj))
    cost: Dict[Pos, int] = dict()
    cost[(si, sj)] = 0

    while que:
        i, j = top = que.popleft()
        cost_top = cost[top]
        if i in row:
            row_idx = bisect_left(row[i], j)
            if row_idx != len(row[i]):
                nxt = (i, row[i][row_idx] - 1)
                if nxt not in cost:
                    cost[nxt] = cost_top + 1
                    que.append(nxt)
            if row_idx != 0:
                nxt = (i, row[i][row_idx - 1] + 1)
                if nxt not in cost:
                    cost[nxt] = cost_top + 1
                    que.append(nxt)

        if j in col:
            col_idx = bisect_left(col[j], i)
            if col_idx != len(col[j]):
                nxt = (col[j][col_idx] - 1, j)
                if nxt not in cost:
                    cost[nxt] = cost_top + 1
                    que.append(nxt)
            if col_idx != 0:
                nxt = (col[j][col_idx - 1] + 1, j)
                if nxt not in cost:
                    cost[nxt] = cost_top + 1
                    que.append(nxt)

    if (gi, gj) in cost:
        print(cost[(gi, gj)])
    else:
        print(-1)


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
