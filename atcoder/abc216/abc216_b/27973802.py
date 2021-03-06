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
    n = int(sinput())
    name = set()
    for _ in range(n):
        st = sinput().strip()
        name.add(st)
    if len(name) == n:
        print("No")
    else:
        print("Yes")


if __name__ == "__main__":
    main()
