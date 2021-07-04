# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import deque

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
    b = deque()
    for i in range(n):
        if i % 2 == 0:
            b.append(a[i])
        else:
            b.appendleft(a[i])

    if n % 2 == 1:
        b.reverse()
    print(*b)


if __name__ == "__main__":
    main()
