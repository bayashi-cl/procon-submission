import functools
import sys
import typing
from collections import deque
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    x = sinput().strip()
    graph: List[List[int]] = [[] for _ in range(n)]
    for i in range(1, n):
        pc = bin(i).count("1")
        graph[i % pc].append(i)

    cost = [IINF] * n
    cost[0] = 0
    que = deque([0])
    while que:
        top = que.popleft()
        for nxt in graph[top]:
            if cost[nxt] == IINF:
                cost[nxt] = cost[top] + 1
                que.append(nxt)

    pop = x.count("1")
    X = int(x, 2)
    m_plus = X % (pop + 1)

    if pop == 0:
        for _ in range(n):
            print(1)
    elif pop == 1:
        for i, xi in enumerate(x):
            if xi == "0":
                to = (m_plus + pow(2, n - i - 1, pop + 1)) % (pop + 1)
                print(cost[to] + 1)
            elif xi == "1":
                print(0)
            else:
                raise ValueError
    else:
        m_minus = X % (pop - 1)
        for i, xi in enumerate(x):
            if xi == "0":
                to = (m_plus + pow(2, n - i - 1, pop + 1)) % (pop + 1)
            elif xi == "1":
                to = (m_minus - pow(2, n - i - 1, pop - 1)) % (pop - 1)
            else:
                raise ValueError
            print(cost[to] + 1)


if __name__ == "__main__":
    main()
