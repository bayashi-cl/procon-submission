# region template
import sys
import typing
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
    s = set()
    n = int(sinput())
    for i in range(n):
        la = list(map(int, sinput().split()))
        a = tuple(la[1:])
        s.add(a)
    print(len(s))


if __name__ == "__main__":
    main()
