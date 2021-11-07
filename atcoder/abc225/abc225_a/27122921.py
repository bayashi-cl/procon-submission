# region template
import sys
import typing
from collections import Counter
from math import factorial
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
    s = sinput().strip()
    cnt = Counter(s)
    ans = factorial(len(s))
    for v in cnt.values():
        ans //= factorial(v)
    print(ans)


if __name__ == "__main__":
    main()
