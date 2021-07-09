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
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    cnt = Counter(a)
    ans = len(cnt)

    even = 0
    for v in cnt.values():
        if v % 2 == 0:
            even += 1

    if even % 2 == 1:
        ans -= 1
    print(ans)


if __name__ == "__main__":
    main()
