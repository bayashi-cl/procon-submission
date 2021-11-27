# region template
import sys
import typing
from collections import Counter
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
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    a.sort()
    ma = a[-1]
    divisible = [False] * (ma + 1)
    for ai in set(a):
        if divisible[ai]:
            continue
        k = 2
        while ai * k <= ma:
            divisible[ai * k] = True
            k += 1

    cnt = Counter(a)
    ans = 0
    for ai in a:
        if cnt[ai] == 1 and not divisible[ai]:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
