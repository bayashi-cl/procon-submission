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
    n, q = map(int, sinput().split())
    back = [-1] * n
    prev = [-1] * n

    for _ in range(q):
        com, *data = map(int, sinput().split())
        if com == 1:
            x, y = data
            x -= 1
            y -= 1
            back[x] = y
            prev[y] = x
        elif com == 2:
            x, y = data
            x -= 1
            y -= 1
            back[x] = -1
            prev[y] = -1
        else:
            (x,) = data
            x -= 1
            ans = deque([x])
            l = prev[x]
            while l != -1:
                ans.appendleft(l)
                l = prev[l]
            r = back[x]
            while r != -1:
                ans.append(r)
                r = back[r]

            print(len(ans), " ".join(map(lambda z: str(z + 1), ans)))


if __name__ == "__main__":
    main()
