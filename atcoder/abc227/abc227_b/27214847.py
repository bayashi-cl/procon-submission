# region template
import sys
import typing
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
    n = int(sinput())
    s = list(map(int, sinput().split()))
    cand = set()
    for a in range(1, 1000):
        for b in range(1, 1000):
            cand.add(4 * a * b + 3 * a + 3 * b)

    ans = 0
    for si in s:
        if si not in cand:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
