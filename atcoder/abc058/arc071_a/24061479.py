# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter
from functools import reduce
from operator import and_

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
    s = [Counter(sinput().strip()) for _ in range(n)]
    cnt: Counter = reduce(and_, s)
    ans = []
    for k, v in cnt.items():
        ans += [k] * v

    ans.sort()
    print("".join(ans))


if __name__ == "__main__":
    main()
