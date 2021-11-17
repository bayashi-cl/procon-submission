# region template
import sys
import typing
from itertools import accumulate
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))

    cs = list(accumulate(a))

    ans = 0
    for i in range(n - 1):
        ans += a[i] * (cs[-1] - cs[i])
        ans %= MOD

    print(ans)


if __name__ == "__main__":
    main()
