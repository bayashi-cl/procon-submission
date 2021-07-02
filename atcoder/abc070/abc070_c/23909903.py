# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
import numpy as np

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
    t = np.zeros(n, dtype=np.int64)
    for i in range(n):
        t[i] = int(sinput())

    print(np.lcm.reduce(t))


if __name__ == "__main__":
    main()
