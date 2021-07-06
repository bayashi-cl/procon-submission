# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
import heapq

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))

    l = a[:n]
    heapq.heapify(l)
    sm = sum(l)
    la = [sm]
    for ai in a[n : 2 * n]:
        m = heapq.heappushpop(l, ai)
        sm += ai - m
        la.append(sm)

    r = [-ai for ai in a[2 * n :]]
    heapq.heapify(r)
    sm = sum(r)
    ra = [-sm]
    for ai in reversed(a[n : 2 * n]):
        m = heapq.heappushpop(r, -ai)
        sm += -ai - m
        ra.append(-sm)

    ans = -INF
    for li, ri in zip(la, reversed(ra)):
        ans = max(ans, li - ri)
    print(ans)


if __name__ == "__main__":
    main()
