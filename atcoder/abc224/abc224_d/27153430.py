# region template
import sys
import typing
from collections import deque
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    m = int(sinput())
    adj: VecVec = [list() for _ in range(9)]
    for i in range(m):
        a, b = map(lambda x: int(x) - 1, sinput().split())
        adj[a].append(b)
        adj[b].append(a)

    p = list(map(lambda x: int(x) - 1, sinput().split()))
    start_ = [8] * 9
    for i, pi in enumerate(p):
        start_[pi] = i

    start = tuple(start_)
    goal = tuple(range(9))

    que: typing.Deque[Tuple[int, ...]] = deque()
    que.append(start)
    cost = {start: 0}

    while que:
        top = que.popleft()
        cost_from = cost[top]
        space = top.index(8)
        for to in adj[space]:
            t_ = list(top)
            t_[space], t_[to] = t_[to], t_[space]
            t = tuple(t_)
            if t not in cost:
                cost[t] = cost_from + 1
                que.append(t)

    print(cost.get(goal, -1))


if __name__ == "__main__":
    main()
