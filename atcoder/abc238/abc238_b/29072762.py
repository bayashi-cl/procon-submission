import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))
    cut: Set[int] = set()
    cut.add(0)
    rotate = 0
    for ai in a:
        rotate += ai
        rotate %= 360
        cut.add(rotate)
    cuts = list(cut)
    cuts.sort()
    ans = 0
    for i in range(len(cuts) - 1):
        ans = max(ans, abs(cuts[i] - cuts[i + 1]))
    ans = max(ans, 360 - cuts[-1] + cuts[0])

    print(ans)


if __name__ == "__main__":
    main()
