# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter

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
    a = list(map(int, sinput().split()))
    cnt = Counter(a)
    ans = 0
    for k, v in cnt.items():
        if v >= k:
            ans += v - k
        else:
            ans += v
    print(ans)


if __name__ == "__main__":
    main()
