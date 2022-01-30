import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

import numpy as np

sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    h, w = map(int, sinput().split())
    a = np.array([list(map(int, sinput().split())) for _ in range(h)])
    b = a.T
    for bi in b:
        print(*bi)


if __name__ == "__main__":
    main()
