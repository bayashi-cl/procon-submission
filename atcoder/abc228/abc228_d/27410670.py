# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
import time

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    q = int(sinput())
    n = 2 ** 20
    a = [-1] * n
    pos = [-1] * n
    for _ in range(q):
        t, x = map(int, sinput().split())
        if t == 1:
            h = x % n
            update = [h]
            while a[h] != -1:
                if pos[h] != -1:
                    h = pos[h]
                else:
                    h = (h + 1) % n
                update.append(h)
            a[h] = x
            for u in update:
                pos[u] = (h + 1) % n
        else:
            print(a[x % n])


if __name__ == "__main__":
    main()
