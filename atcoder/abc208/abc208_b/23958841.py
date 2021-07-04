# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    p = int(sinput())
    coin = []
    for i in range(1, 11):
        c = 1
        for j in range(1, i + 1):
            c *= j
        coin.append(c)

    coin.reverse()
    ans = 0
    for c in coin:
        d, m = divmod(p, c)
        ans += d
        p = m

    print(ans)


if __name__ == "__main__":
    main()
