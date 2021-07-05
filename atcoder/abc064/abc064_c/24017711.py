# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion
"""
1    - 399  ：灰色
400  - 799  ：茶色
800  - 1199 ：緑色
1200 - 1599 ：水色
1600 - 1999 ：青色
2000 - 2399 ：黄色
2400 - 2799 ：橙色
2800 - 3199 ：赤色
"""


def main() -> None:
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    s = set()
    free = 0

    for ai in a:
        d = ai // 400
        if d >= 8:
            free += 1
        else:
            s.add(d)

    print(max(len(s), 1), len(s) + free)


if __name__ == "__main__":
    main()
