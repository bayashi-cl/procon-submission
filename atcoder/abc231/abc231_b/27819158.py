# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter

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
    cnt = Counter([sinput().strip() for _ in range(n)])
    print(cnt.most_common(1)[0][0])


if __name__ == "__main__":
    main()
