# region template
import sys
import typing
from operator import itemgetter
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
    n, d = map(int, sinput().split())
    lr = [tuple(map(int, sinput().split())) for _ in range(n)]
    lr.sort(key=itemgetter(1))
    now = 0
    ans = 0
    for l, r in lr:
        if l < now:
            continue
        if r >= now:
            ans += 1
            now = r + d
    print(ans)


if __name__ == "__main__":
    main()
