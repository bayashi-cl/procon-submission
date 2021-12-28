# region template
import sys
import typing
from collections import Counter
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
    _, x = map(int, sinput().split())
    a = Counter(map(int, sinput().split()))
    print(a[x])


if __name__ == "__main__":
    main()
