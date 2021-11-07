# region template
import sys
import typing
from functools import reduce
from operator import and_
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
    ab = [set(map(int, sinput().split())) for _ in range(n - 1)]
    res = reduce(and_, ab)
    if res:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
