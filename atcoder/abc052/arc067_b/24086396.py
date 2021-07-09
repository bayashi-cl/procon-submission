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
    n, a, b = map(int, sinput().split())
    x = np.array(sinput().split(), dtype=np.int64)
    diff = np.diff(x) * a
    diff = np.where(diff >= b, b, diff)
    print(np.sum(diff))


if __name__ == "__main__":
    main()
